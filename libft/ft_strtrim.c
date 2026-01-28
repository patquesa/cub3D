/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:02:28 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/19 13:09:16 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1)
	{
		return (NULL);
	}
	if (!set)
	{
		return (NULL);
	}
	j = ft_strlen(s1);
	i = 0;
	while ((s1[i] && ft_strchr(set, s1[i])))
	{
		i++;
	}
	while (j > i && ft_strchr(set, s1[j - 1]))
	{
		j--;
	}
	result = ft_substr(s1, i, j - i);
	return (result);
}

/*
int	main(void)
{
	char s1[] = "xxHello worldxx";
	char set[] = "x";
	char *result = ft_strtrim(s1, set);
	
	if (result)
	{
		printf("s1:%s\n", s1);
		printf("result:%s\n", result);
	}
	else
	{
		printf("failed\n");
	}
	return (0);	
}*/