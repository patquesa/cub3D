/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 13:28:29 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/31 13:49:50 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//por ejemplo &g->cfg.north (quita espacios,..evita duplicado y guarda ruta en dst)
int	set_path_once(char **dst, const char *payload)
{
	char	*trimmed; //Variable temporal para guardar el “payload” → el texto que contiene la ruta

	if (*dst != NULL) //si ya tenias una ruta, es duplicado (error)
		return (fail("Duplicate texture identifier"));
	trimmed = ft_strtrim(payload, " \t\r"); //Quita espacios/tabs/\r a izquierda y derecha del payload.
	if (!trimmed || trimmed[0] == '\0')
	{
		free(trimmed);
		return (fail("Invalid texture path"));
	}
	*dst = ft_strdup(trimmed); //Duplica ruta y la guardas definitivamente en dst
	free(trimmed);
	return (*dst == NULL);
}
