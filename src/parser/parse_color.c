/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 13:21:46 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 19:27:00 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* devuelve 1 si es uno de los ss (es decir q se permite) */
/* Check if character is whitespace (space, tab, or carriage return) */
int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\r');
}

/* Parse de un componente 0..255, permitiendo espacios alrededor. 
Convertir un string q rpta un num a un int*/

/* Parse one RGB component (0..255), allowing surrounding spaces.
   Convert a string representing a number to an int */
static int	parse_rgb_comp(const char *s, int *out)
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

/* Count the number of commas in a string */
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

/* que solo sean dos coma en lugar correcto (no empiece o termine con , ni ,,) */
/* Check for bad comma placement (starts/ends with comma, or double commas) */
static int	has_bad_commas(const char *s)
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

/* Separa por comas, valida 3 numeros, comprueba rango de 0-255 y 
guarda en g->floor_color[0],..[1],[2] */
/* Split by commas, validate 3 numbers, check 0-255 range and store in 
rgb array */
int	parse_color_payload(const char *payload, int rgb[3])
{
	char	**parts;

	if (has_bad_commas(payload))
		return (fail("Invalid commas"));
	parts = ft_split(payload, ',');
	if (!parts)
		return (1);
	if (!parts[0] || !parts[1] || !parts[2] || parts[3])
		return (ft_split_free(parts), fail("Invalid color"));
	if (parse_rgb_comp(parts[0], &rgb[0]) //si la conversion de string a int salio mal, free
		|| parse_rgb_comp(parts[1], &rgb[1])
		|| parse_rgb_comp(parts[2], &rgb[2]))
		return (ft_split_free(parts), fail("Invalid color"));
	ft_split_free(parts);
	return (0);
}
