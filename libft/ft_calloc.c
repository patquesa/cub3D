/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:39:56 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/17 12:41:37 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = malloc (nmemb * size);
	if (!ptr)
	{
		return (NULL);
	}
	while (i < nmemb * size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

/*
int	main(void)
{
	int	*str;
	size_t count;
	size_t i;

	count = 5;
	i = 0;
	str = (int*)ft_calloc(count, sizeof(int));
	if (!str)
		return (1);
	while (i < count)
	{
		printf("str[%zu] = %d\n", i, str[i]);
		i++;
	}
	free(str);
	return (0);
}*/