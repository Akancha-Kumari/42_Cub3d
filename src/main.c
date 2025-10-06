/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:38:17 by akumari           #+#    #+#             */
/*   Updated: 2025/10/06 16:27:44 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// <-- store map pointer in game for colors/textures
int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	ft_memset(&game, 0, sizeof(t_game));
	ft_memset(&map, 0, sizeof(t_map));
	if (argc != 2)
		error_exit("Usage: ./cub3D mapfile");
	parse_map(argv[1], &map);
	if (!map.map_grid)
		error_exit("Failed to parse map.");
	game.map = map.map_grid;
	game.map_struct = &map;
	init_player(&game);
	init_graphics(&game);
	init_textures(&game, &map);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	cleanup_game(&game);
	if (map.arena)
		arena_destroy(map.arena);
	return (0);
}

// int main(int argc, char **argv)
// {
// 	t_game game;
// 	ft_memset(&game, 0, sizeof(t_game));

// 	if (argc != 2)
// 		error_exit("Usage: ./cub3D mapfile");
// 	t_map map;
// 	parse_map(argv[1], &map);
// 	game.map = map.map_grid;
// 	init_player(&game);
// 	init_graphics(&game);
// 	init_textures(&game);
// 	mlx_loop_hook(game.mlx, render_frame, &game);
// 	mlx_key_hook(game.mlx, key_hook, &game);
// 	mlx_loop(game.mlx);

// 	cleanup_game(&game);
// 	arena_destroy(map.arena);
// 	return (0);
// }

// Akancha ft_mlx is the modification of your main function.
// I put your init_payer function to init_payer_dir fuction.
// The rest is the same. I hope this is okay for you.

// int	main(int argc, char **argv)
// {
// 	t_map	map;

// 	if (argc != 2)
// 		error_exit("Input: ./cub3D mapfile");
// 	parse_map(argv[1], &map);
// //	ft_mlx(&map);
// 	arena_destroy(map.arena);
// }

// static void init_player_dir(t_game *game, char c)
// {
// 	if (c == 'N')
// 	{
// 		game->player_dir_y = -1;
// 		game->player_plane_x = 0.66;
// 	}
// 	else if (c == 'S')
// 	{
// 		game->player_dir_y = 1;
// 		game->player_plane_x = -0.66;
// 	}
// 	else if (c == 'E')
// 	{
// 		game->player_dir_x = 1;
// 		game->player_plane_y = 0.66;
// 	}
// 	else if (c == 'W')
// 	{
// 		game->player_dir_x = -1;
// 		game->player_plane_y = -0.66;
// 	}
// }

// static void init_game(t_map *map, t_game *game)
// {
// 	ft_bzero(game, sizeof(t_game));
// 	game->player_pos_x = map->player_x + 0.5;
// 	game->player_pos_y = map->player_y + 0.5;
// 	gamp->map = map->map_grid;
// 	game->map[map->player_y][map->player_x] = '0';
// 	init_player_dir(game, map->player_dir);
// 	game->arena = map->arena;
// }

// static void ft_mlx(t_map *map)
// {
// 	t_game game;

// 	init_game(map, &game);
// 	init_graphic(&game);
// 	mlx_loop_hook(game.mlx, render_frame, &game);
// 	mlx_key_hook(game.mlx, key_hook, &game);
// 	mlx_loop(game.mlx);
// 	mlx_terminate(game.mlx);
// }
