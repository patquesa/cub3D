/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 13:28:29 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 19:31:15 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Check if a texture file exists and has .png extension */
static int	validate_texture_file(const char *trimmed)
{
	int		fd;
	size_t	len;

	if (!trimmed || trimmed[0] == '\0')
		return (fail("Empty texture path"));
	len = ft_strlen(trimmed);
	if (len < 4 || ft_strncmp(trimmed + len - 4, ".png", 5) != 0)
		return (fail("Texture must be a .png file"));
	fd = open(trimmed, O_RDONLY);
	if (fd < 0)
		return (fail("Texture file does not exist"));
	close(fd);
	return (0);
}

//por ejemplo &g->cfg.north (quita espacios,..evita duplicado y guarda ruta en dst)
int	set_path_once(char **dst, const char *payload)
{
	char	*trimmed; //Variable temporal para guardar el "payload" → el texto que contiene la ruta

	if (*dst != NULL) //si ya tenias una ruta, es duplicado (error)
		return (fail("Duplicate texture identifier"));
	trimmed = ft_strtrim(payload, " \t\r"); //Quita espacios/tabs/\r a izquierda y derecha del payload.
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		return (fail("Invalid texture path"));
	}
	if (validate_texture_file(trimmed) != 0)
	{
		free(trimmed);
		return (1);
	}
	*dst = ft_strdup(trimmed); //Duplica ruta y la guardas definitivamente en dst
	free(trimmed);
	return (*dst == NULL);
}
