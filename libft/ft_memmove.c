/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:15:00 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/15 11:44:07 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	s = (char *) src;
	d = (char *) dest;
	if (!dest && !src)
		return (0);
	if (d < s)
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	else
	{
		d += n;
		s += n;
		while (n--)
		{
			*(--d) = *(--s);
		}
	}
	return (dest);
}

/*int	main(void)
{
	char	src[20] = "Hello World";
	char	dest[20] = "Hi World";
	
	printf("Antes: %s\n", dest);
	ft_memmove (dest, src, 11);
	printf("Despues:%s\n", dest);
	memmove(dest, src, 11);
	printf("original:%s\n", dest);
	return (0);
}*/
