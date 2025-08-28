/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:54:12 by ji-hong           #+#    #+#             */
/*   Updated: 2025/08/18 23:32:33 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*f_line_join(char *line, char *s, size_t n)
{
	size_t	tmp_len;
	char	*tmp;

	tmp = line;
	if (!line)
		tmp_len = 0;
	else
		tmp_len = ft_strlen(tmp);
	line = (char *)malloc(tmp_len + n + 1);
	if (!line)
	{
		free(tmp);
		return (NULL);
	}
	if (tmp_len)
	{
		ft_memcpy(line, tmp, tmp_len);
		free (tmp);
	}
	ft_memcpy(line + tmp_len, s, n);
	line[tmp_len + n] = 0;
	ft_memcpy(s, s + n, ft_strlen(s) - n + 1);
	return (line);
}

int	f_newline_index(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (i);
		i ++;
	}
	return (-1);
}

char	*f_read_buffer(int fd, char *buffer)
{
	int		rd;
	int		l_len;
	char	*line;

	line = NULL;
	rd = ft_strlen(buffer);
	if (!rd)
		rd = read(fd, buffer, BUFFER_SIZE);
	while (rd > 0)
	{
		buffer[rd] = 0;
		l_len = f_newline_index(buffer) + 1;
		if (!l_len)
			line = f_line_join(line, buffer, rd);
		else
			line = f_line_join(line, buffer, l_len);
		if (!line || l_len)
			return (line);
		rd = read(fd, buffer, BUFFER_SIZE);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = f_read_buffer(fd, buffer);
	return (line);
}
