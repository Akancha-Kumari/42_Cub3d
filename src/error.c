/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:38:08 by akumari           #+#    #+#             */
/*   Updated: 2025/10/02 16:48:10 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/parse.h"

void	error_exit(char *error_msg)
{
	printf("Error\n%s\n", error_msg);
	exit(EXIT_FAILURE);
}

void	line_exit(t_arena *arena, char *line, char *error_msg)
{
	free(line);
	arena_destroy(arena);
	error_exit(error_msg);
}

void	arena_exit(t_arena *arena, char *error_msg)
{
	arena_destroy(arena);
	error_exit(error_msg);
}

void	cleanup_game(t_game *game)
{
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
}
