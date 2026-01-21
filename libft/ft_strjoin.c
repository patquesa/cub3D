/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:38:11 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/18 14:23:38 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!s3)
	{
		return (NULL);
	}
	while (s1[i])
	{
		s3[j++] = s1[i++];
	}
	i = 0;
	while (s2[i])
	{
		s3[j++] = s2[i++];
	}
	s3[j] = '\0';
	return (s3);
}
/*
int	main(void)
{
	char *s1;
	char *s2;
	char *s3;

	s1 = "hello ";
	s2 = "world";
	s3 = ft_strjoin(s1, s2);
	printf("s3:%s\n", s3);
	return (0);
}*/