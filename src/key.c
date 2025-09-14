#include "../include/cub3d.h"

static void move_forward_backward(t_game *game, int forward)
{
	double move_speed = 0.1;
	if (forward)
	{
		if (game->map[(int)game->player_pos_y]
					 [(int)(game->player_pos_x + game->player_dir_x * move_speed)] == '0')
			game->player_pos_x += game->player_dir_x * move_speed;
		if (game->map[(int)(game->player_pos_y + game->player_dir_y * move_speed)]
					 [(int)game->player_pos_x] == '0')
			game->player_pos_y += game->player_dir_y * move_speed;
	}
	else
	{
		if (game->map[(int)game->player_pos_y]
					 [(int)(game->player_pos_x - game->player_dir_x * move_speed)] == '0')
			game->player_pos_x -= game->player_dir_x * move_speed;
		if (game->map[(int)(game->player_pos_y - game->player_dir_y * move_speed)]
					 [(int)game->player_pos_x] == '0')
			game->player_pos_y -= game->player_dir_y * move_speed;
	}
}

static void move_strafe(t_game *game, int right)
{
	double move_speed = 0.1;
	if (right)
	{
		if (game->map[(int)game->player_pos_y]
					 [(int)(game->player_pos_x + game->player_plane_x * move_speed)] == '0')
			game->player_pos_x += game->player_plane_x * move_speed;
		if (game->map[(int)(game->player_pos_y + game->player_plane_y * move_speed)]
					 [(int)game->player_pos_x] == '0')
			game->player_pos_y += game->player_plane_y * move_speed;
	}
	else
	{
		if (game->map[(int)game->player_pos_y]
					 [(int)(game->player_pos_x - game->player_plane_x * move_speed)] == '0')
			game->player_pos_x -= game->player_plane_x * move_speed;
		if (game->map[(int)(game->player_pos_y - game->player_plane_y * move_speed)]
					 [(int)game->player_pos_x] == '0')
			game->player_pos_y -= game->player_plane_y * move_speed;
	}
}

static void rotate_player(t_game *game, int right)
{
	double rot_speed = 0.05;
	double old_dir_x = game->player_dir_x;
	double old_plane_x = game->player_plane_x;
	double angle = (right) ? rot_speed : -rot_speed;

	game->player_dir_x = game->player_dir_x * cos(angle) - game->player_dir_y * sin(angle);
	game->player_dir_y = old_dir_x * sin(angle) + game->player_dir_y * cos(angle);

	game->player_plane_x = game->player_plane_x * cos(angle) - game->player_plane_y * sin(angle);
	game->player_plane_y = old_plane_x * sin(angle) + game->player_plane_y * cos(angle);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game = param;

	if (keydata.action != MLX_PRESS && keydata.action != MLX_REPEAT)
		return;
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

// void key_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_game *game = param;
// 	double move_speed = 0.1;
// 	double rot_speed = 0.05;

// 	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
// 	{
// 		if (keydata.key == MLX_KEY_ESCAPE)
// 			mlx_close_window(game->mlx);

// 		// Move forward
// 		if (keydata.key == MLX_KEY_W)
// 		{
// 			if (game->map[(int)(game->player_pos_y)][(int)(game->player_pos_x + game->player_dir_x * move_speed)] == '0')
// 				game->player_pos_x += game->player_dir_x * move_speed;
// 			if (game->map[(int)(game->player_pos_y + game->player_dir_y * move_speed)][(int)(game->player_pos_x)] == '0')
// 				game->player_pos_y += game->player_dir_y * move_speed;
// 		}

// 		// Move backward
// 		if (keydata.key == MLX_KEY_S)
// 		{
// 			if (game->map[(int)(game->player_pos_y)][(int)(game->player_pos_x - game->player_dir_x * move_speed)] == '0')
// 				game->player_pos_x -= game->player_dir_x * move_speed;
// 			if (game->map[(int)(game->player_pos_y - game->player_dir_y * move_speed)][(int)(game->player_pos_x)] == '0')
// 				game->player_pos_y -= game->player_dir_y * move_speed;
// 		}

// 		// Strafe left (A key)
// 		if (keydata.key == MLX_KEY_A)
// 		{
// 			if (game->map[(int)(game->player_pos_y)][(int)(game->player_pos_x - game->player_plane_x * move_speed)] == '0')
// 				game->player_pos_x -= game->player_plane_x * move_speed;
// 			if (game->map[(int)(game->player_pos_y - game->player_plane_y * move_speed)][(int)(game->player_pos_x)] == '0')
// 				game->player_pos_y -= game->player_plane_y * move_speed;
// 		}

// 		// Strafe right (D key)
// 		if (keydata.key == MLX_KEY_D)
// 		{
// 			if (game->map[(int)(game->player_pos_y)][(int)(game->player_pos_x + game->player_plane_x * move_speed)] == '0')
// 				game->player_pos_x += game->player_plane_x * move_speed;
// 			if (game->map[(int)(game->player_pos_y + game->player_plane_y * move_speed)][(int)(game->player_pos_x)] == '0')
// 				game->player_pos_y += game->player_plane_y * move_speed;
// 		}

// 		// Rotate left
// 		if (keydata.key == MLX_KEY_LEFT)
// 		{
// 			double old_dir_x = game->player_dir_x;
// 			game->player_dir_x = game->player_dir_x * cos(-rot_speed) - game->player_dir_y * sin(-rot_speed);
// 			game->player_dir_y = old_dir_x * sin(-rot_speed) + game->player_dir_y * cos(-rot_speed);

// 			double old_plane_x = game->player_plane_x;
// 			game->player_plane_x = game->player_plane_x * cos(-rot_speed) - game->player_plane_y * sin(-rot_speed);
// 			game->player_plane_y = old_plane_x * sin(-rot_speed) + game->player_plane_y * cos(-rot_speed);
// 		}

// 		// Rotate right
// 		if (keydata.key == MLX_KEY_RIGHT)
// 		{
// 			double old_dir_x = game->player_dir_x;
// 			game->player_dir_x = game->player_dir_x * cos(rot_speed) - game->player_dir_y * sin(rot_speed);
// 			game->player_dir_y = old_dir_x * sin(rot_speed) + game->player_dir_y * cos(rot_speed);

// 			double old_plane_x = game->player_plane_x;
// 			game->player_plane_x = game->player_plane_x * cos(rot_speed) - game->player_plane_y * sin(rot_speed);
// 			game->player_plane_y = old_plane_x * sin(rot_speed) + game->player_plane_y * cos(rot_speed);
// 		}
// 	}
// }
