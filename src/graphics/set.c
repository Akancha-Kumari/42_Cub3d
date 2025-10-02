/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:48:33 by akumari           #+#    #+#             */
/*   Updated: 2025/10/02 14:51:32 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

// Handles north/south directions
static void	set_player_dir_ns(t_game *game, char c)
{
	if (c == 'N')
	{
		game->player_dir_x = 0;
		game->player_dir_y = -1;
		game->player_plane_x = 0.66;
		game->player_plane_y = 0;
	}
	else if (c == 'S')
	{
		game->player_dir_x = 0;
		game->player_dir_y = 1;
		game->player_plane_x = -0.66;
		game->player_plane_y = 0;
	}
}

// Handles east/west directions
static void	set_player_dir_ew(t_game *game, char c)
{
	if (c == 'E')
	{
		game->player_dir_x = 1;
		game->player_dir_y = 0;
		game->player_plane_x = 0;
		game->player_plane_y = 0.66;
	}
	else if (c == 'W')
	{
		game->player_dir_x = -1;
		game->player_dir_y = 0;
		game->player_plane_x = 0;
		game->player_plane_y = -0.66;
	}
}

// Main wrapper function that chooses the correct helper
void	set_player_dir(t_game *game, char c)
{
	if (c == 'N' || c == 'S')
		set_player_dir_ns(game, c);
	else if (c == 'E' || c == 'W')
		set_player_dir_ew(game, c);
}
