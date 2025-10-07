/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:38:17 by akumari           #+#    #+#             */
/*   Updated: 2025/10/07 15:54:32 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
