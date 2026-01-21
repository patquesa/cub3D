/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 12:03:02 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/16 18:13:35 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sig;
	int	res;

	i = 0;
	sig = 1;
	res = 0;
	while ((nptr[i] == 32) || ((nptr[i] >= 9) && (nptr[i] <= 13)))
	{
		i++;
	}
	if ((nptr[i] == '-') || (nptr[i] == '+'))
	{
		if (nptr[i] == '-')
		{
			sig *= -1;
		}
		i++;
	}
	while (nptr[i] >= 48 && nptr[i] <= 57)
	{
		res = ((nptr[i] - '0') + (res * 10));
		i++;
	}
	return (res * sig);
}

/*
int	main(void)
{
	const char *ptr1;
	const char *ptr2;
	int	ent;
	
	ptr1 = "123";
	ptr2 = "  -345";
	ent = ft_atoi(ptr1);
	printf("%d\n", ent);
	ent = ft_atoi(ptr2);
	printf("%d\n", ent);
	return (0);
}*/