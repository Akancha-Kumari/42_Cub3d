/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:37:24 by akumari           #+#    #+#             */
/*   Updated: 2025/10/02 15:18:02 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/game.h"

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

static void	move_forward_backward(t_game *game, int forward)
{
	double	move_speed;
	int		dir;
	double	dx;
	double	dy;

	move_speed = 0.1;
	if (forward)
		dir = 1;
	else
		dir = -1;
	dx = game->player_dir_x * move_speed * dir;
	dy = game->player_dir_y * move_speed * dir;
	apply_movement(game, dx, dy);
}

// sideways movement
static void	move_strafe(t_game *game, int right)
{
	double	move_speed;
	int		dir;
	double	dx;
	double	dy;

	move_speed = 0.1;
	if (right)
		dir = 1;
	else
		dir = -1;
	dx = game->player_plane_x * move_speed * dir;
	dy = game->player_plane_y * move_speed * dir;
	apply_movement(game, dx, dy);
}

static void	rotate_player(t_game *game, int right)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;
	double	angle;

	rot_speed = 0.05;
	old_dir_x = game->player_dir_x;
	old_plane_x = game->player_plane_x;
	if (right)
		angle = rot_speed;
	else
		angle = -rot_speed;
	game->player_dir_x = game->player_dir_x * cos(angle) - game->player_dir_y
		* sin(angle);
	game->player_dir_y = old_dir_x * sin(angle) + game->player_dir_y
		* cos(angle);
	game->player_plane_x = game->player_plane_x * cos(angle)
		- game->player_plane_y * sin(angle);
	game->player_plane_y = old_plane_x * sin(angle) + game->player_plane_y
		* cos(angle);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return ;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_W)
		move_forward_backward(game, 1);
	else if (keydata.key == MLX_KEY_S)
		move_forward_backward(game, 0);
	else if (keydata.key == MLX_KEY_A)
		move_strafe(game, 0);
	else if (keydata.key == MLX_KEY_D)
		move_strafe(game, 1);
	else if (keydata.key == MLX_KEY_LEFT)
		rotate_player(game, 0);
	else if (keydata.key == MLX_KEY_RIGHT)
		rotate_player(game, 1);
}

// static void	move_forward_backward(t_game *game, int forward)
// {
// 	double	move_speed;
// 	double	next_x;
// 	double	next_y;
// 	double	back_x;
// 	double	back_y;

// 	move_speed = 0.1;
// 	next_x = game->player_pos_x + game->player_dir_x * move_speed;
// 	next_y = game->player_pos_y + game->player_dir_y * move_speed;
// 	back_x = game->player_pos_x - game->player_dir_x * move_speed;
// 	back_y = game->player_pos_y - game->player_dir_y * move_speed;
// 	if (forward)
// 	{
// 		if (game->map[(int)game->player_pos_y][(int)(next_x)] == '0')
// 			game->player_pos_x += game->player_dir_x * move_speed;
// 		if (game->map[(int)(next_y)][(int)game->player_pos_x] == '0')
// 			game->player_pos_y += game->player_dir_y * move_speed;
// 	}
// 	else
// 	{
// 		if (game->map[(int)game->player_pos_y][(int)(back_x)] == '0')
// 			game->player_pos_x -= game->player_dir_x * move_speed;
// 		if (game->map[(int)(back_y)][(int)game->player_pos_x] == '0')
// 			game->player_pos_y -= game->player_dir_y * move_speed;
// 	}
// }

// // sideways movement
// static void	move_strafe(t_game *game, int right)
// {
// 	double	move_speed;
// 	double	next_right_x;
// 	double	next_right_y;
// 	double	next_left_x;
// 	double	next_left_y;

// 	move_speed = 0.1;
// 	next_right_x = game->player_pos_x + game->player_plane_x * move_speed;
// 	next_right_y = game->player_pos_y + game->player_plane_y * move_speed;
// 	next_left_x = game->player_pos_x - game->player_plane_x * move_speed;
// 	next_left_y = game->player_pos_y - game->player_plane_y * move_speed;
// 	if (right)
// 	{
// 		if (game->map[(int)game->player_pos_y][(int)next_right_x] == '0')
// 			game->player_pos_x = next_right_x;
// 		if (game->map[(int)next_right_y][(int)game->player_pos_x] == '0')
// 			game->player_pos_y = next_right_y;
// 	}
// 	else
// 	{
// 		if (game->map[(int)game->player_pos_y][(int)next_left_x] == '0')
// 			game->player_pos_x = next_left_x;
// 		if (game->map[(int)next_left_y][(int)game->player_pos_x] == '0')
// 			game->player_pos_y = next_left_y;
// 	}
// }