/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 15:24:40 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/19 13:43:07 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;
	size_t				i;

	str1 = (const unsigned char *) s1;
	str2 = (const unsigned char *) s2;
	i = 0;
	while (i < n)
	{
		if (str1[i] != str2[i])
		{
			return (str1[i] - str2[i]);
		}
		i++;
	}
	return (0);
}

/*
int	main(void)
{
	char	str1[] = "Hello World";
	char	str2[] = "Hello World";
	char	str3[] = "Hello children";
	int	result; 

	result = ft_memcmp(str1, str2, 10);
	if (result == 0)
	{
		printf("son iguales\n");
	}
	else
	{
		printf ("son diferentes\n");
		printf("Diferencia:%d\n", result);
	}
	result = ft_memcmp (str1, str3, 10);
	if (result == 0)
	{
		printf("son iguales\n");
	}
	else
	{
		printf("son diferentes\n");
		printf("Diferencia:%d\n", result);
	}
	return (0);
}*/
