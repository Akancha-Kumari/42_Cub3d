/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 14:01:00 by ji-hong           #+#    #+#             */
/*   Updated: 2025/08/28 19:27:01 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <stdio.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../arena/arena.h"
# include "../get_next_line/get_next_line.h"

typedef struct s_map
{
	int		w;
	int		h;
	int		f[3];
	int		c[3];
	int		player_x;
	int		player_y;
	char	*map_start;
	char	*map_end;
	char	player_dir;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	**map_grid;
	t_arena	*arena;
}	t_map;

//parse_map.c
void	parse_map(char *file, t_map *map);

//parse_read.c
void	chk_map(t_map *map, char *line);
void	read_file(char *file, t_map *map);

//parse_texture.c
void	chk_texture_color(t_map *map, char *line);

//parse_util.c
int		chk_filename(char *name, char *extension);
int		ft_isspace(int c);
char	*trim_front(char *s);
int		ft_isemptystring(char *s);
void	trim_rear(char *s);

//error.c
void	error_exit(char *error_msg);
void	line_exit(t_arena *arena, char *line, char *error_msg);
void	arena_exit(t_arena *arena, char *error_msg);

#endif
