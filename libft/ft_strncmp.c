/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 13:23:18 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/11 16:39:44 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 != '\0' || *s2 != '\0') && n > 0)
	{
		if (*s1 != *s2)
		{
			return ((unsigned char)*s1 - (unsigned char)*s2);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

/*int	main(void)
{
	char	s1[] = "hello";
	char	s2[] = "world";
	int	n = 4;
	
	printf("original: %d\n", strncmp(s1, s2, n));
	printf("despues: %d\n", ft_strncmp(s1, s2, n));
	return (0);
}*/
