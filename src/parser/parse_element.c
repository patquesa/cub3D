/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 13:23:07 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/28 12:27:27 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_ws(char c) //devuelve 1 si es uno de los ss (es decir q se permite)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

//por ejemplo &g->cfg.north (quita espacios,..evita duplicado y guarda ruta en dst)
static int	set_path_once(char **dst, const char *payload)
{
	char	*trimmed; //Variable temporal para guardar el “payload” → el texto que contiene la ruta

	if (*dst != NULL) //si ya tenias una ruta, es duplicado (error)
		return (1);
	trimmed = ft_strtrim(payload, " \t\r"); //Quita espacios/tabs/\r a izquierda y derecha del payload.
	if (!trimmed || trimmed[0] == '\0') //si malloc falla o payload vacia
		return (free(trimmed), 1);
	*dst = ft_strdup(trimmed); //Duplica ruta y la guardas definitivamente en dst
	free(trimmed);
	return (*dst == NULL);
}

/* Parse de un componente 0..255, permitiendo espacios alrededor */
static int	parse_rgb_comp(const char *s, int *out) //convertir un string q rpta un num a un int
{
	long	val; //num q vamos construyendo
	int		i; //iterador por string

	if (!s || !*s) //si s es NULL o cadena vacia
		return (1);
	i = 0;
	while (s[i] && is_ws(s[i])) //ignoramos espacios iniciales, tabs y retorno...
		i++;
	if (s[i] < '0' || s[i] > '9')
		return (1);
	val = 0;
	while (s[i] >= '0' && s[i] <= '9') //lee los digitos del numero
	{
		val = val * 10 + (s[i] - '0');
		if (val > 255)
			return (1);
		i++;
	}
	while (s[i] && is_ws(s[i])) //salta espacios despues del numero
		i++;
	if (s[i] != '\0')
		return (1);
	*out = (int)val;
	return (0); //ok
}

static int	count_commas(const char *s)
{
	int	i;
	int	c;

	i = 0;
	c = 0;
	while (s[i])
	{
		if (s[i] == ',')
			c++;
		i++;
	}
	return (c);
}

static int	has_bad_commas(const char *s) //que solo sean dos coma en lugar correcto (no empiece o termine con , ni ,,)
{
	int	i;

	if (!s || !*s)
		return (1);
	if (s[0] == ',')
		return (1);
	i = 0;
	while (s[i])
	{
		if (s[i] == ',' && s[i + 1] == ',')
			return (1);
		i++;
	}
	if (i > 0 && s[i - 1] == ',')
		return (1);
	if (count_commas(s) != 2)
		return (1);
	return (0);
}

//separa por comas, valida 3 numeros, comprueba rango de 0-255 y guarda en g->floor_color[0],..[1],[2]
static int	parse_color_payload(const char *payload, int rgb[3])
{
	char	**parts;

	if (has_bad_commas(payload))
		return (1);
	parts = ft_split(payload, ',');
	if (!parts)
		return (1);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
		return (ft_split_free(parts), 1);
	if (parse_rgb_comp(parts[0], &rgb[0]) //si la conversion de string a int salio mal, free
		|| parse_rgb_comp(parts[1], &rgb[1])
		|| parse_rgb_comp(parts[2], &rgb[2]))
		return (ft_split_free(parts), 1);
	ft_split_free(parts);
	return (0);
}
//Convierte RGB a uint32 RGBA (útil para MLX42 al pintar) 
static uint32_t	rgb_to_rgba_u32(int r, int g, int b)
{
	return ((uint32_t)r << 24) | ((uint32_t)g << 16) | ((uint32_t)b << 8) | 255u;
}

//si linea valida (0), error (1)
int	parse_header_element(const char *line, t_game *g)
{
//Si los 2 primeros son NO... y el tercer caracter es espacio, tab... (is_ws)
	if (ft_strncmp(line, "NO", 2) == 0 && is_ws(line[2]))//line +2 payload es todo lo que viene despues de NO..
		return (set_path_once(&g->cfg.north, line + 2)); //set_path quita espacios, evita duplicado y guarda ruta
	if (ft_strncmp(line, "SO", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->cfg.south, line + 2));
	if (ft_strncmp(line, "WE", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->cfg.west, line + 2));
	if (ft_strncmp(line, "EA", 2) == 0 && is_ws(line[2]))
		return (set_path_once(&g->cfg.east, line + 2));

	/* Colores */
	if (line[0] == 'F' && is_ws(line[1])) //si primer caracter es F (floor) y ss espacio (evita F220,100,0 error)
	{   //COLOR SUELO
		if (g->cfg.floor_set) //si floor_set = 1 es q ya habia un F anterior
			return (1); // duplicados de F
		if (parse_color_payload(line + 2, g->cfg.floor_color) != 0)//line+2 salta F y esp para llegar al numero (ej."220,100,0")
			return (1);
		g->cfg.floor_set = 1;//marcas q has leido color de floor
		g->floor = rgb_to_rgba_u32(g->cfg.floor_color[0],
				g->cfg.floor_color[1], g->cfg.floor_color[2]);
		return (0);//linea F valida
	} //COLOR TECHO (misma logica anterior)
	if (line[0] == 'C' && is_ws(line[1]))
	{
		if (g->cfg.ceiling_set)
			return (1); // duplicado
		if (parse_color_payload(line + 2, g->cfg.ceiling_color) != 0)
			return (1);
		g->cfg.ceiling_set = 1;
		g->ceiling = rgb_to_rgba_u32(g->cfg.ceiling_color[0],
				g->cfg.ceiling_color[1], g->cfg.ceiling_color[2]);
		return (0);
	}
	return (1); // línea inválida dentro de la cabecera (no habia NO/SO..ni F, C)
}
