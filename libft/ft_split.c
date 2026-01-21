/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 11:25:42 by patquesa          #+#    #+#             */
/*   Updated: 2024/12/22 16:37:23 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_initiate_vars(size_t *i, int *j, int *start_word)
{
	*i = 0;
	*j = 0;
	*start_word = -1;
}

static int	word_count(const char *s, char c)
{
	int	count;
	int	inside_word;

	count = 0;
	inside_word = 0;
	while (*s)
	{
		if (*s != c && inside_word == 0)
		{
			inside_word = 1;
			count++;
		}
		else if (*s == c)
		{
			inside_word = 0;
		}
		s++;
	}
	return (count);
}

static char	*fill_word(const char *s, int start, int end)
{
	char	*new_word;
	int		i;

	i = 0;
	new_word = malloc((end - start + 1) * sizeof(char));
	if (!new_word)
	{
		return (NULL);
	}
	while (start < end)
	{
		new_word[i] = s[start];
		i++;
		start++;
	}
	new_word[i] = 0;
	return (new_word);
}

static void	*ft_free(char **strs, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	size_t	i;
	int		j;
	int		start_word;

	ft_initiate_vars(&i, &j, &start_word);
	result = malloc((word_count(s, c) + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start_word < 0)
			start_word = i;
		else if ((s[i] == c || s[i] == '\0') && start_word >= 0)
		{
			result[j] = fill_word(s, start_word, i);
			if (!result[j++])
				return (ft_free(result, j - 1));
			start_word = -1;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

/*
int	main(void)
{
	char const s[] = "hello world 42 ";
	char c = ' ';
	char ** result;
	int	i;
	
	result = ft_split(s, c);
	if (result == NULL)
		printf("return:NULL");
	
	i = 0;
	while (result[i] != NULL)
	{
		printf("result[%d]:%s\n", i, result[i]);
		i++;
	}
	ft_free(result, i);
	return (0);
}*/