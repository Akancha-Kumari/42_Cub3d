/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji.hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 19:54:52 by ji-hong           #+#    #+#             */
/*   Updated: 2025/08/18 23:33:11 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# if BUFFER_SIZE <= -2
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include "../libft/libft.h"

char	*get_next_line(int fd);
/*
char	*f_read_buffer(int fd, char *buffer);
char	*f_line_join(char *line, char *s, size_t n);
int		f_newline_index(char *s);
*/

#endif
