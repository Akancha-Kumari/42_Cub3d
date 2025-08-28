/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:43:46 by ji-hong           #+#    #+#             */
/*   Updated: 2025/08/27 14:33:13 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static void	texture_file_chk(t_map *map, char *line, char *file)
{
	int	fd;

	if (chk_filename(file, ".png"))
		line_exit(map->arena, line, "textures: .png file format");
	fd = open(file, O_RDONLY);
	if (fd == -1)
		line_exit(map->arena, line, "texture file open failed");
	close(fd);
}

static void	get_texture(t_map *map, char *line, char *s)
{
	char	*file;
	char	*tmp;

	file = s + 2;
	file = trim_front(file);
	texture_file_chk(map, line, file);
	tmp = arena_strdup(map->arena, file);
	if (!tmp)
		line_exit(map->arena, line, "memory allocation failed");
	if (*s == 'N' && !map->no)
		map->no = tmp;
	else if (*s == 'S' && !map->so)
		map->so = tmp;
	else if (*s == 'W' && !map->we)
		map->we = arena_strdup(map->arena, file);
	else if (*s == 'E' && !map->ea)
		map->ea = tmp;
	else
		line_exit(map->arena, line, "texture info error");
}

static int	color_value(t_map *map, char *line, char **s)
{
	int		n;
	char	*tmp;

	tmp = *s;
	if (*tmp == '+')
		tmp ++;
	if (!ft_isdigit(*tmp))
		line_exit(map->arena, line, "invalid color value");
	n = 0;
	while (ft_isdigit(*tmp))
	{
		if (n > 255)
			line_exit(map->arena, line, "invalid color value");
		n = n * 10 + *tmp - '0';
		tmp ++;
	}
	*s = tmp;
	return (n);
}

static void	get_color(t_map *map, char *line, char *s, char c)
{
	int		i;

	s += 2;
	s = trim_front(s);
	i = 0;
	while (i < 3)
	{
		if (c == 'F' && map->f[i] == -1)
			map->f[i] = color_value(map, line, &s);
		else if (c == 'C' && map->c[i] == -1)
			map->c[i] = color_value(map, line, &s);
		else
			line_exit(map->arena, line, "color info error");
		s = trim_front(s);
		if (i < 2)
		{
			if (*s != ',')
				line_exit(map->arena, line, "color info error");
			s ++;
		}
		i ++;
	}
	if (*s)
		line_exit(map->arena, line, "invalid color value");
}

void	chk_texture_color(t_map *map, char *line)
{
	char	*s;

	if (ft_isemptystring(line))
		return ;
	s = trim_front(line);
	trim_rear(s);
	if (!ft_strncmp(s, "NO ", 3) || !ft_strncmp(s, "SO ", 3)
		|| !ft_strncmp(s, "WE ", 3) || !ft_strncmp(s, "EA ", 3))
		get_texture(map, line, s);
	else if (!ft_strncmp(s, "F ", 2) || !ft_strncmp(s, "C ", 2))
		get_color(map, line, s, *s);
	else if (*s == '1' && map->no && map->so && map->we && map->ea
		&& map->f[0] != -1 && map->c[0] != -1)
		chk_map(map, line);
	else
		line_exit(map->arena, line, "invalid information detected");
}
