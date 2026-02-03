/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adruz-to <adruz-to@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/31 13:28:29 by patquesa          #+#    #+#             */
/*   Updated: 2026/02/03 17:35:08 by adruz-to         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	*dst = ft_strdup(trimmed);
	free(trimmed);
	return (*dst == NULL);
}
