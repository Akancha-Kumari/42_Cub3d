/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:37:04 by akumari           #+#    #+#             */
/*   Updated: 2025/10/02 17:23:37 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_player(t_game *game)
{
	char	c;
	int		y;
	int		x;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player_pos_x = x + 0.5;
				game->player_pos_y = y + 0.5;
				set_player_dir(game, c);
				game->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_graphics(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!game->mlx)
		error_exit("Failed to initialize MLX.");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		error_exit("Failed to create image buffer.");
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		error_exit("Failed to display image.");
}

void	init_textures(t_game *game, t_map *map)
{
	game->tex_north = mlx_load_png(map->no);
	game->tex_south = mlx_load_png(map->so);
	game->tex_east = mlx_load_png(map->ea);
	game->tex_west = mlx_load_png(map->we);
	if (!game->tex_north || !game->tex_south || !game->tex_east
		|| !game->tex_west)
		error_exit("Failed to load textures from map file.");
}
