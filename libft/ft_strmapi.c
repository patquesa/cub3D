/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:37:36 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/21 10:44:46 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	str = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
	{
		return (NULL);
	}
	i = 0;
	while (s[i])
	{
		str[i] = f(i, s[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}

/*
char	to_uppercase(unsigned int i, char c)
{	
	(void)i;
		
	if (c >= 'a' && c <= 'z')
	{
		return (c - 32);
	}
	return (c);
}

int	main(void)
{
	char *s;
	char *new_str;

	s = "hello";
	new_str = ft_strmapi(s, &to_uppercase);
	printf("%s\n", new_str);
	free(new_str);
	return (0);
}*/
