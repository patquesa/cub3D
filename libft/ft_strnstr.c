/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 17:09:33 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/16 11:55:43 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*little == '\0')
	{
		return ((char *)big);
	}
	while (big[i] != '\0' && i < len)
	{
		if (big[i] == little[0])
		{
			while ((big[i + j] == little[j]) && i + j < len)
			{
				if (little[j + 1] == '\0')
				{
					return ((char *)big + i);
				}
				j++;
			}
		}
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	const char	*b = "hello world";
	const char	*l = "world";
	size_t n = 12;
	
	printf("%s\n", ft_strnstr(b, l, n));
	return (0);
}*/