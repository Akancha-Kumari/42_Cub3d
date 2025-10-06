/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 18:36:02 by akumari           #+#    #+#             */
/*   Updated: 2025/10/06 18:36:05 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	apply_movement(t_game *game, double dx, double dy)
{
	if (game->map[(int)game->player_pos_y][(int)(game->player_pos_x
		+ dx)] == '0')
	{
		game->player_pos_x += dx;
	}
	if (game->map[(int)(game->player_pos_y
			+ dy)][(int)game->player_pos_x] == '0')
	{
		game->player_pos_y += dy;
	}
}

static void	process_rotation(t_game *game)
{
	double	rot_speed;
	double	angle;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = 0.01;
	if (game->input.left || game->input.right)
	{
		angle = 0.0;
		if (game->input.right)
			angle += rot_speed;
		if (game->input.left)
			angle -= rot_speed;
		old_dir_x = game->player_dir_x;
		old_plane_x = game->player_plane_x;
		game->player_dir_x = game->player_dir_x * cos(angle)
			- game->player_dir_y * sin(angle);
		game->player_dir_y = old_dir_x * sin(angle) + game->player_dir_y
			* cos(angle);
		game->player_plane_x = game->player_plane_x * cos(angle)
			- game->player_plane_y * sin(angle);
		game->player_plane_y = old_plane_x * sin(angle) + game->player_plane_y
			* cos(angle);
	}
}

static void	move_forward_backward(t_game *game, double *dx, double *dy)
{
	double	move_speed;

	move_speed = 0.02;
	if (game->input.w)
	{
		*dx += game->player_dir_x * move_speed;
		*dy += game->player_dir_y * move_speed;
	}
	if (game->input.s)
	{
		*dx -= game->player_dir_x * move_speed;
		*dy -= game->player_dir_y * move_speed;
	}
}

static void	move_strafe(t_game *game, double *dx, double *dy)
{
	double	move_speed;

	move_speed = 0.02;
	if (game->input.d)
	{
		*dx += game->player_plane_x * move_speed;
		*dy += game->player_plane_y * move_speed;
	}
	if (game->input.a)
	{
		*dx -= game->player_plane_x * move_speed;
		*dy -= game->player_plane_y * move_speed;
	}
}

void	process_movement(t_game *game)
{
	double	dx;
	double	dy;

	dx = 0;
	dy = 0;
	move_forward_backward(game, &dx, &dy);
	move_strafe(game, &dx, &dy);
	if ((game->input.w || game->input.s) && (game->input.a || game->input.d))
	{
		dx *= 0.7071;
		dy *= 0.7071;
	}
	apply_movement(game, dx, dy);
	process_rotation(game);
}
