/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/26 09:26:49 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/26 09:28:43 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_next(char *back)
{
	int		i;
	char	*new_back;
	char	*new_line;

	new_line = ft_strchr(back, '\n');
	if (!new_line)
	{
		free (back);
		return (NULL);
	}
	i = new_line - back + 1;
	new_back = ft_strjoin("", back + i);
	free(back);
	return (new_back);
}

char	*ft_free(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}
