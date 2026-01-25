/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: patquesa <patquesa@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:18:36 by patquesa          #+#    #+#             */
/*   Updated: 2026/01/25 20:11:22 by patquesa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
static char	*back[MAX_FD];


char	*ft_free(char *str)
{
	free(str);
	str = NULL;
	return (NULL);
}

char	*read_file(int fd, char *buffer, char *back)
{
	char	*tmp;
	int		n_bytes;

	n_bytes = 1;
	while (n_bytes > 0)
	{
		n_bytes = read(fd, buffer, BUFFER_SIZE);
		if (n_bytes == -1)
		{
			buffer = ft_free(buffer);
			back = ft_free(back);
			return (NULL);
		}
		buffer[n_bytes] = '\0';
		tmp = back;
		back = ft_strjoin(back, buffer);
		free(tmp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(buffer);
	return (back);
}

char	*ft_line(char *back)
{
	char	*line;
	char	*new_line;
	int		i;

	if (!back || !*back)
		return (NULL);
	new_line = ft_strchr(back, '\n');
	if (new_line)
		i = new_line - back;
	else
		i = ft_strlen(back);
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_memcpy(line, back, i);
	if (new_line)
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_next(char *back)
{
	int		i;
	char	*new_back;
	char	*new_line;

	new_line = ft_strchr(back, '\n');
	if (!new_line)
	{
		free (back);
		return (NULL);
	}
	i = new_line - back + 1;
	new_back = ft_strjoin("", back + i);
	free(back);
	return (new_back);
}

char	*get_next_line(int fd)
{
	char	*buffer;
	char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	back[fd] = read_file(fd, buffer, back[fd]);
	if (!back[fd])
		return (NULL);
	line = ft_line(back[fd]);
	back[fd] = ft_next(back[fd]);
	return (line);
}

void	gnl_reset(int fd)
{
	if (fd < 0 || fd >= MAX_FD)
		return ;
	free(back[fd]);
	back[fd] = NULL;
}



/*char	*get_next_line(int fd)
{
	static char	*back;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FD)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	back = read_file(fd, buffer, back);
	if (!back)
	{
		return (NULL);
	}
	line = ft_line(back);
	back = ft_next(back);
	return (line);
}*/
