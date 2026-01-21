/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 09:29:30 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/18 13:38:38 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	i;

	dst_len = 0;
	src_len = 0;
	i = 0;
	while (src[src_len] != '\0')
		src_len++;
	while (dst[dst_len] != '\0' && dst_len < size)
		dst_len++;
	if (size <= dst_len)
		return (size + src_len);
	while ((src[i] != '\0') && (dst_len + i) < size - 1)
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (dst_len + src_len);
}

/*int	main(void)
{
	char	dst[20] = "Hello ";
	const	char *src = "world";
	size_t	size = sizeof(dst);
	size_t result; 
	
	result = ft_strlcat(dst, src, size);
	printf("cadena concatenada:%s\n", dst);
	printf("longitud:%zu\n", result);
	return (0);
}*/
