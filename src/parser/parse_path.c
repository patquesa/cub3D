/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 13:28:29 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/04 13:09:41 by adruz-to         ###   ########.fr       */
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

/* Set texture path once, preventing duplicates */
int	set_path_once(char **dst, const char *payload)
{
	char	*trimmed;

	if (*dst != NULL)
		return (fail("Duplicate texture identifier"));
	trimmed = ft_strtrim(payload, " \t\r");
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
	*dst = ft_strdup(trimmed);
	free(trimmed);
	return (*dst == NULL);
}
