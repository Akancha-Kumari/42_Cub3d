/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:47:51 by ji-hong           #+#    #+#             */
/*   Updated: 2025/10/03 15:57:17 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static void	copy_map(t_map *map)
{
	int	i;
	int	len;

	if (!map->player_dir)
		arena_exit(map->arena, "No player info");
	map->map_grid = arena_alloc(map->arena, sizeof(char *) * (map->h + 1));
	if (!map->map_grid)
		arena_exit(map->arena, "memory allocation failed");
	i = 0;
	while (i < map->h)
	{
		map->map_grid[i] = arena_alloc(map->arena, map->w + 1);
		len = ft_strlen(map->map_start);
		ft_memcpy(map->map_grid[i], map->map_start, len);
		map->map_start = map->map_start + len + 1;
		while (len < map->w)
		{
			map->map_grid[i][len] = ' ';
			len ++;
		}
		map->map_grid[i][len] = 0;
		i ++;
	}
	map->map_grid[map->h] = NULL;
}

static void	validate_map(t_map *map, char **grid)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->h)
	{
		j = 0;
		while (j < map->w)
		{
			if (grid[i][j] != '1' && grid[i][j] != ' ')
			{
				if (i == 0 || i == map->h - 1 || j == 0
					|| j == map->w - 1)
					arena_exit(map->arena, "wall missing");
				else if (grid[i - 1][j] == ' '
					|| grid[i + 1][j] == ' '
					|| grid[i][j - 1] == ' '
					|| grid[i][j + 1] == ' ')
					arena_exit(map->arena, "wall missing");
			}
			j ++;
		}
		i ++;
	}
}

static void	print_result(t_map *map)
{
	int	i;

	printf("NO %s\nSO %s\nWE %s\nEA %s\n", map->no, map->so, map->we, map->ea);
	printf("C %d, %d, %d\nF %d, %d, %d\n", map->c[0], map->c[1],
		map->c[2], map->f[0], map->f[1], map->f[2]);
	i = 0;
	while (map->map_grid[i])
	{
		printf("%s\n", map->map_grid[i]);
		i ++;
	}
}

void	parse_map(char *file, t_map *map)
{
	if (chk_filename(file, ".cub"))
		error_exit(".cub file format for the map");
	read_file(file, map);
	copy_map(map);
	validate_map(map, map->map_grid);
	print_result(map);
}
