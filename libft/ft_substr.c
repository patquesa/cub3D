/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 17:26:44 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/19 12:40:36 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*subs;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	subs = ft_calloc(len + 1, sizeof(char));
	if (!subs)
	{
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		subs[i] = s[start + i];
		i++;
	}
	return (subs);
}

/*
int	main(void)
{
	char const *s1;
	char *s2;

	s1 = "Hello, world";
	s2 = ft_substr(s1, 7, 5);
	if (!s2)
	{
		printf("not found\n");
		return (1);
	}
	else
	{
		printf("s2:%s\n", s2);
		free(s2);
	} 
	return (0);
}*/