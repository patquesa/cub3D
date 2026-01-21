/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 12:18:21 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/15 13:59:13 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	ch;
	size_t			i;

	i = 0;
	str = (unsigned char *) s;
	ch = (unsigned char) c;
	while (i < n)
	{
		if (str[i] == ch)
		{
			return ((void *)str + i);
		}
		i++;
	}
	return (NULL);
}

/*
int	main(void)
{
	char	str[] = "Hello World";
	
	if (ft_memchr(str, 'W', 12) != NULL)
		printf("Encontrado:W\n");
	else
		printf("no encontrado:\n");
	
	if (ft_memchr(str, 'p', 12) != NULL)
		printf("encontrado:p\n");
	else
		printf("No encontrado:\n");
	return (0);	
}*/
