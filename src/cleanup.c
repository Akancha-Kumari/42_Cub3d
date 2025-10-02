/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 17:44:05 by akumari           #+#    #+#             */
/*   Updated: 2025/10/02 18:01:42 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	cleanup_map(t_map *map)
{
	int	y;

	if (!map || !map->map_grid)
		return ;
	y = 0;
	while (map->map_grid[y])
	{
		free(map->map_grid[y]);
		y++;
	}
	free(map->map_grid);
	map->map_grid = NULL;
}

// Main cleanup function
void	cleanup_game(t_game *game)
{
	game->map = NULL;
	if (game->tex_north)
		mlx_delete_texture(game->tex_north);
	if (game->tex_south)
		mlx_delete_texture(game->tex_south);
	if (game->tex_east)
		mlx_delete_texture(game->tex_east);
	if (game->tex_west)
		mlx_delete_texture(game->tex_west);
	if (game->img)
		mlx_delete_image(game->mlx, game->img);
	if (game->mlx)
		mlx_terminate(game->mlx);
	game->mlx = NULL;
	game->img = NULL;
	game->tex_north = NULL;
	game->tex_south = NULL;
	game->tex_east = NULL;
	game->tex_west = NULL;
}

// game->map = NULL;
// void	cleanup_game(t_game *game)
// {
// 	if (game->tex_north)
// 		mlx_delete_texture(game->tex_north);
// 	if (game->tex_south)
// 		mlx_delete_texture(game->tex_south);
// 	if (game->tex_east)
// 		mlx_delete_texture(game->tex_east);
// 	if (game->tex_west)
// 		mlx_delete_texture(game->tex_west);
// 	if (game->img)
// 		mlx_delete_image(game->mlx, game->img);
// 	if (game->mlx)
// 		mlx_terminate(game->mlx);
// }
