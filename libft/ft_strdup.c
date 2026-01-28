/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 13:00:17 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/18 11:50:14 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*s2;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	s2 = (char *)malloc (sizeof(char) * (len + 1));
	if (!s2)
	{
		return (NULL);
	}
	while (s[i])
	{
		s2[i] = s[i];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}

/*
int	main(void)
{
	const char *s1;
	char *s2;

	s1 = "hello";
	s2 = ft_strdup(s1);
	if (!s2)
	{
		printf("not found\n");
		return (1);
	}
	else
	{
		printf("s1:%s\n", s1);
		printf("s2:%s\n", s2);
		free(s2);
	}
	return (0);
}*/