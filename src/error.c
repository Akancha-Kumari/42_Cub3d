/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:38:08 by akumari           #+#    #+#             */
/*   Updated: 2025/10/02 17:59:31 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/parse.h"

void	error_exit(char *error_msg)
{
	printf("Error\n%s\n", error_msg);
	exit(EXIT_FAILURE);
}

void	error_exit_graphic(char *msg, t_game *game, t_map *map)
{
	if (game || map)
		cleanup_game(game);
	printf("Error\n%s\n", msg);
	exit(EXIT_FAILURE);
}

void	line_exit(t_arena *arena, char *line, char *error_msg)
{
	free(line);
	if (arena)
		arena_destroy(arena);
	error_exit(error_msg);
}

void	arena_exit(t_arena *arena, char *error_msg)
{
	if (arena)
		arena_destroy(arena);
	error_exit(error_msg);
}
