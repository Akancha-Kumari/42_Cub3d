/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 20:06:31 by ji-hong           #+#    #+#             */
/*   Updated: 2025/08/27 13:46:48 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static void	init_map(t_map *map)
{
	ft_bzero(map, sizeof(t_map));
	map->f[0] = -1;
	map->f[1] = -1;
	map->f[2] = -1;
	map->c[0] = -1;
	map->c[1] = -1;
	map->c[2] = -1;
	map->arena = arena_create(ARENA_SIZE);
	if (!map->arena)
		error_exit("memory allocation failed");
}

static int	get_player_info(t_map *map, char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '0' || line[i] == '1' || line[i] == ' ')
			i ++;
		else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E'
			|| line[i] == 'W')
		{
			if (!map->player_dir)
			{
				map->player_dir = line[i];
				map->player_x = i;
				map->player_y = map->h;
			}
			else
				line_exit(map->arena, line, "multiple players");
			i ++;
		}
		else
			line_exit(map->arena, line, "invalid map element");
	}
	return (i);
}

void	chk_map(t_map *map, char *line)
{
	int		i;
	char	*s;

	trim_rear(line);
	if (!line[0])
	{
		map->map_end = map->arena->memory + map->arena->offset - 1;
		return ;
	}
	i = get_player_info(map, line);
	if (!map->map_start)
	{
		map->map_start = arena_strdup(map->arena, line);
		if (!map->map_start)
			line_exit(map->arena, line, "memory allocation failed");
	}
	else
	{
		s = arena_strdup(map->arena, line);
		if (!map->map_start)
			line_exit(map->arena, line, "memory allocation failed");
	}
	if (i > map->w)
		map->w = i;
	map->h ++;
}

static void	read_line(int fd, t_map *map, char *line)
{
	while (line)
	{
		if (!map->map_start)
			chk_texture_color(map, line);
		else if (!map->map_end)
			chk_map(map, line);
		else if (!ft_isemptystring(line))
			line_exit(map->arena, line, "invalid information");
		free(line);
		line = get_next_line(fd);
	}
}

void	read_file(char *file, t_map *map)
{
	int		fd;
	char	*line;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_exit("map file open failed");
	init_map(map);
	line = get_next_line(fd);
	if (!line)
		line_exit(map->arena, line, "no infor from the map");
	read_line(fd, map, line);
	close(fd);
	if (!map->map_start)
		line_exit(map->arena, line, "map missing");
	if (!map->map_end)
		map->map_end = map->arena->memory + map->arena->offset - 1;
}
