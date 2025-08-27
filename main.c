/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:47:51 by ji-hong           #+#    #+#             */
/*   Updated: 2025/08/27 15:50:52 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

static void	init_player_dir(t_game *game, char c)
{
	if (c == 'N')
	{
		game->player_dir_y = -1;
		game->player_plane_x = 0.66;
	}
	else if (c == 'S')
	{
		game->player_dir_y = 1;
		game->player_plane_x = -0.66;
	}
	else if (c == 'E')
	{
		game->player_dir_x = 1;
		game->player_plane_y = 0.66;
	}
	else if (c == 'W')
	{
		game->player_dir_x = -1;
		game->player_plane_y = -0.66;
	}
}

static void	init_game(t_map *map, t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->player_pos_x = map->player_x + 0.5;
	game->player_pos_y = map->player_y + 0.5;
	gamp->map = map->map_grid;
	game->map[map->player_y][map->player_x] = '0';
	init_player_dir(game, map->player_dir);
	game->arena = map->arena;
}

static void	ft_mlx(t_map *map)
{
	t_game	game;

	init_game(map, &game);
	init_graphic(&game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
}

int	main(int argc, char **argv)
{
	t_map	map;

	if (argc != 2)
		error_exit("Input: ./cub3D mapfile");
	parse_map(argv[1], &map);
	ft_mlx(&map);
	arena_destroy(map.arena);
}
