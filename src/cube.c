#include "../include/cub3d.h"

void error_exit(const char *msg)
{
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game = param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(game->mlx);
}

#include <math.h>

void render_frame(void *param)
{
	t_game *game = param;
	int x;

	// Clear image each frame (so it redraws fresh)
	mlx_delete_image(game->mlx, game->img);
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(game->mlx, game->img, 0, 0);

	for (x = 0; x < WIDTH; x++)
	{
		double camera_x = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
		double ray_dir_x = game->player_dir_x + game->player_plane_x * camera_x;
		double ray_dir_y = game->player_dir_y + game->player_plane_y * camera_x;

		int map_x = (int)game->player_pos_x;
		int map_y = (int)game->player_pos_y;

		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);

		double side_dist_x;
		double side_dist_y;

		int step_x;
		int step_y;

		int hit = 0;
		int side;

		// Calculate step and initial sideDist
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->player_pos_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player_pos_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->player_pos_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player_pos_y) * delta_dist_y;
		}

		// DDA loop
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game->map[map_y][map_x] == '1')
				hit = 1;
		}

		// Calculate distance to wall
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - game->player_pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - game->player_pos_y + (1 - step_y) / 2) / ray_dir_y;

		// Calculate height of line
		int line_height = (int)(HEIGHT / perp_wall_dist);

		// Calculate draw range
		int draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

		// Simple colors: different for each wall side
		uint32_t color = (side == 1) ? 0xFF5555FF : 0xFF0000FF;

		// Draw vertical line
		for (int y = draw_start; y <= draw_end; y++)
		{
			mlx_put_pixel(game->img, x, y, color);
		}
	}
}

void init_player(t_game *game)
{
	int y = 0;
	while (game->map[y])
	{
		int x = 0;
		while (game->map[y][x])
		{
			char c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player_pos_x = x + 0.5;
				game->player_pos_y = y + 0.5;

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
				else if (c == 'E')
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
				game->map[y][x] = '0';
				return;
			}
			x++;
		}
		y++;
	}
}

void init_graphics(t_game *game)
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

int main(void)
{
	t_game game;
	memset(&game, 0, sizeof(t_game));

	char map_data[][7] = {
		"111111",
		"100101",
		"101001",
		"1100N1",
		"111111"};
	char *map[6];
	int i = 0;
	while (i < 5)
	{
		map[i] = map_data[i];
		i++;
	}
	map[5] = NULL;
	game.map = map;
	init_player(&game);
	init_graphics(&game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
