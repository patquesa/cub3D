/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 10:12:47 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/22 17:03:31 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while ((s[i]))
	{
		(*f)(i, &s[i]);
		i++;
	}
}

/*
void	to_uppercase(unsigned int i, char *c)
{
	(void)	i;
	if (*c >= 97 && *c <= 122)
	{
		*c = *c - 32;
	}
}


int	main(void)
{
	char s[] = "hello world";

	ft_striteri(s, to_uppercase);
	printf("Result:%s\n", s);
	return (0);
}*/