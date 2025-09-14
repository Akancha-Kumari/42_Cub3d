#include "../include/cub3d.h"

void error_exit(const char *msg)
{
	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void init_textures(t_game *game)
{
	// Example: four wall textures (N, S, E, W)
	game->tex_north = mlx_load_png("./textures/north.png");
	game->tex_south = mlx_load_png("./textures/south.png");
	game->tex_east = mlx_load_png("./textures/east.png");
	game->tex_west = mlx_load_png("./textures/west.png");

	if (!game->tex_north || !game->tex_south || !game->tex_east || !game->tex_west)
		error_exit("Failed to load textures.");
}

void key_hook(mlx_key_data_t keydata, void *param)
{
	t_game *game = param;
	double move_speed = 0.1;
	double rot_speed = 0.05;

	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_ESCAPE)
			mlx_close_window(game->mlx);

		// Move forward
		if (keydata.key == MLX_KEY_W)
		{
			if (game->map[(int)(game->player_pos_y)][(int)(game->player_pos_x + game->player_dir_x * move_speed)] == '0')
				game->player_pos_x += game->player_dir_x * move_speed;
			if (game->map[(int)(game->player_pos_y + game->player_dir_y * move_speed)][(int)(game->player_pos_x)] == '0')
				game->player_pos_y += game->player_dir_y * move_speed;
		}

		// Move backward
		if (keydata.key == MLX_KEY_S)
		{
			if (game->map[(int)(game->player_pos_y)][(int)(game->player_pos_x - game->player_dir_x * move_speed)] == '0')
				game->player_pos_x -= game->player_dir_x * move_speed;
			if (game->map[(int)(game->player_pos_y - game->player_dir_y * move_speed)][(int)(game->player_pos_x)] == '0')
				game->player_pos_y -= game->player_dir_y * move_speed;
		}

		// Strafe left (A key)
		if (keydata.key == MLX_KEY_A)
		{
			if (game->map[(int)(game->player_pos_y)][(int)(game->player_pos_x - game->player_plane_x * move_speed)] == '0')
				game->player_pos_x -= game->player_plane_x * move_speed;
			if (game->map[(int)(game->player_pos_y - game->player_plane_y * move_speed)][(int)(game->player_pos_x)] == '0')
				game->player_pos_y -= game->player_plane_y * move_speed;
		}

		// Strafe right (D key)
		if (keydata.key == MLX_KEY_D)
		{
			if (game->map[(int)(game->player_pos_y)][(int)(game->player_pos_x + game->player_plane_x * move_speed)] == '0')
				game->player_pos_x += game->player_plane_x * move_speed;
			if (game->map[(int)(game->player_pos_y + game->player_plane_y * move_speed)][(int)(game->player_pos_x)] == '0')
				game->player_pos_y += game->player_plane_y * move_speed;
		}

		// Rotate left
		if (keydata.key == MLX_KEY_LEFT)
		{
			double old_dir_x = game->player_dir_x;
			game->player_dir_x = game->player_dir_x * cos(-rot_speed) - game->player_dir_y * sin(-rot_speed);
			game->player_dir_y = old_dir_x * sin(-rot_speed) + game->player_dir_y * cos(-rot_speed);

			double old_plane_x = game->player_plane_x;
			game->player_plane_x = game->player_plane_x * cos(-rot_speed) - game->player_plane_y * sin(-rot_speed);
			game->player_plane_y = old_plane_x * sin(-rot_speed) + game->player_plane_y * cos(-rot_speed);
		}

		// Rotate right
		if (keydata.key == MLX_KEY_RIGHT)
		{
			double old_dir_x = game->player_dir_x;
			game->player_dir_x = game->player_dir_x * cos(rot_speed) - game->player_dir_y * sin(rot_speed);
			game->player_dir_y = old_dir_x * sin(rot_speed) + game->player_dir_y * cos(rot_speed);

			double old_plane_x = game->player_plane_x;
			game->player_plane_x = game->player_plane_x * cos(rot_speed) - game->player_plane_y * sin(rot_speed);
			game->player_plane_y = old_plane_x * sin(rot_speed) + game->player_plane_y * cos(rot_speed);
		}
	}
}

void render_frame(void *param)
{
	t_game *game = param;
	uint32_t *pixels = (uint32_t *)game->img->pixels;
	int total_pixels = WIDTH * HEIGHT;

	// -----------------------------
	// 1. Fill ceiling & floor
	// -----------------------------
	for (int i = 0; i < (HEIGHT / 2) * WIDTH; i++)
		pixels[i] = 0xAAAAAAFF; // light gray ceiling
	for (int i = (HEIGHT / 2) * WIDTH; i < total_pixels; i++)
		pixels[i] = 0x444444FF; // dark gray floor

	// -----------------------------
	// 2. Raycasting loop
	// -----------------------------
	for (int x = 0; x < WIDTH; x++)
	{
		// Camera space
		double camera_x = 2 * x / (double)WIDTH - 1;
		double ray_dir_x = game->player_dir_x + game->player_plane_x * camera_x;
		double ray_dir_y = game->player_dir_y + game->player_plane_y * camera_x;

		// Starting grid square
		int map_x = (int)game->player_pos_x;
		int map_y = (int)game->player_pos_y;

		// Delta distances
		double delta_dist_x = fabs(1 / ray_dir_x);
		double delta_dist_y = fabs(1 / ray_dir_y);

		double side_dist_x;
		double side_dist_y;
		int step_x;
		int step_y;
		int hit = 0;
		int side;

		// Calculate step and initial side_dist
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

		// -----------------------------
		// 3. DDA loop
		// -----------------------------
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

		// -----------------------------
		// 4. Distance to wall
		// -----------------------------
		double perp_wall_dist;
		if (side == 0)
			perp_wall_dist = (map_x - game->player_pos_x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - game->player_pos_y + (1 - step_y) / 2) / ray_dir_y;

		// -----------------------------
		// 5. Pick texture based on side
		// -----------------------------
		mlx_texture_t *texture;
		if (side == 0)
		{
			if (ray_dir_x > 0)
				texture = game->tex_west;
			else
				texture = game->tex_east;
		}
		else
		{
			if (ray_dir_y > 0)
				texture = game->tex_north;
			else
				texture = game->tex_south;
		}

		// -----------------------------
		// 6. Wall height on screen
		// -----------------------------
		int line_height = (int)(HEIGHT / perp_wall_dist);

		int draw_start = -line_height / 2 + HEIGHT / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + HEIGHT / 2;
		if (draw_end >= HEIGHT)
			draw_end = HEIGHT - 1;

		// -----------------------------
		// 7. Texture X coordinate
		// -----------------------------
		double wall_x;
		if (side == 0)
			wall_x = game->player_pos_y + perp_wall_dist * ray_dir_y;
		else
			wall_x = game->player_pos_x + perp_wall_dist * ray_dir_x;
		wall_x -= floor(wall_x);

		int tex_x = (int)(wall_x * (double)texture->width);
		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
			tex_x = texture->width - tex_x - 1;

		// -----------------------------
		// 8. Vertical texture mapping
		// -----------------------------
		// double step = 1.0 * texture->height / line_height;
		// double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;

		// uint32_t *tex_pixels = (uint32_t *)texture->pixels;
		// for (int y = draw_start; y <= draw_end; y++)
		// {
		// 	int tex_y = (int)tex_pos & (texture->height - 1);
		// 	tex_pos += step;

		// 	uint32_t color = tex_pixels[tex_y * texture->width + tex_x];
		// 	mlx_put_pixel(game->img, x, y, color);
		// }
		double step = (double)texture->height / line_height;
		double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;

		uint32_t *tex_pixels = (uint32_t *)texture->pixels;

		for (int y = draw_start; y <= draw_end; y++)
		{
			int tex_y = (int)tex_pos;
			if (tex_y >= (int)texture->height)
				tex_y = texture->height - 1; // clamp instead of bitmask
			tex_pos += step;

			uint32_t color = tex_pixels[tex_y * texture->width + tex_x];

			// Convert BGRA → RGBA (MLX42 stores pixels as BGRA)
			uint8_t b = (color >> 0) & 0xFF;
			uint8_t g = (color >> 8) & 0xFF;
			uint8_t r = (color >> 16) & 0xFF;
			uint8_t a = (color >> 24) & 0xFF;

			// Force opaque if you don’t want transparency issues
			if (a == 0)
				a = 0xFF;
			uint32_t fixed_color = (r << 24) | (g << 16) | (b << 8) | a;
			mlx_put_pixel(game->img, x, y, fixed_color);
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
	init_textures(&game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_key_hook(game.mlx, key_hook, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}

// void key_hook(mlx_key_data_t keydata, void *param)
// {
// 	t_game *game = param;
// 	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
// 		mlx_close_window(game->mlx);
// }

// void render_frame(void *param)
// {
// 	t_game *game = param;
// 	int x;

// 	// Clear image each frame (so it redraws fresh)

// 	// mlx_delete_image(game->mlx, game->img);
// 	// game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
// 	// mlx_image_to_window(game->mlx, game->img, 0, 0);
// 	uint32_t *pixels = (uint32_t *)game->img->pixels;
// 	int total_pixels = WIDTH * HEIGHT * sizeof(uint32_t);
// 	// for (int i = 0; i < total_pixels; i++)
// 	// {
// 	// 	pixels[i] = 0x000000FF;
// 	// }
// 	memset(pixels, 0, total_pixels);

// 	for (x = 0; x < WIDTH; x++)
// 	{
// 		double camera_x = 2 * x / (double)WIDTH - 1; // x-coordinate in camera space
// 		double ray_dir_x = game->player_dir_x + game->player_plane_x * camera_x;
// 		double ray_dir_y = game->player_dir_y + game->player_plane_y * camera_x;

// 		int map_x = (int)game->player_pos_x;
// 		int map_y = (int)game->player_pos_y;

// 		double delta_dist_x = fabs(1 / ray_dir_x);
// 		double delta_dist_y = fabs(1 / ray_dir_y);

// 		double side_dist_x;
// 		double side_dist_y;

// 		int step_x;
// 		int step_y;

// 		int hit = 0;
// 		int side;

// 		// Calculate step and initial sideDist
// 		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (game->player_pos_x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - game->player_pos_x) * delta_dist_x;
// 		}
// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (game->player_pos_y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - game->player_pos_y) * delta_dist_y;
// 		}

// 		// DDA loop
// 		while (hit == 0)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (game->map[map_y][map_x] == '1')
// 				hit = 1;
// 		}

// 		// Calculate distance to wall
// 		double perp_wall_dist;
// 		if (side == 0)
// 			perp_wall_dist = (map_x - game->player_pos_x + (1 - step_x) / 2) / ray_dir_x;
// 		else
// 			perp_wall_dist = (map_y - game->player_pos_y + (1 - step_y) / 2) / ray_dir_y;

// 		// Calculate height of line
// 		int line_height = (int)(HEIGHT / perp_wall_dist);

// 		// Calculate draw range
// 		int draw_start = -line_height / 2 + HEIGHT / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		int draw_end = line_height / 2 + HEIGHT / 2;
// 		if (draw_end >= HEIGHT)
// 			draw_end = HEIGHT - 1;

// 		// Simple colors: different for each wall side
// 		uint32_t color = (side == 1) ? 0xFF5555FF : 0xFF0000FF;

// 		// Draw vertical line
// 		for (int y = draw_start; y <= draw_end; y++)
// 		{
// 			mlx_put_pixel(game->img, x, y, color);
// 		}
// 	}
// }

// void render_frame(void *param)
// {
// 	t_game *game = param;
// 	uint32_t *pixels = (uint32_t *)game->img->pixels;
// 	int total_pixels = WIDTH * HEIGHT;

// 	// Fill ceiling (top half) with light gray
// 	for (int i = 0; i < (HEIGHT / 2) * WIDTH; i++)
// 		pixels[i] = 0xAAAAAAFF;

// 	// Fill floor (bottom half) with dark gray
// 	for (int i = (HEIGHT / 2) * WIDTH; i < total_pixels; i++)
// 		pixels[i] = 0x444444FF;

// 	// --- Raycasting loop (same as your version) ---
// 	for (int x = 0; x < WIDTH; x++)
// 	{
// 		double camera_x = 2 * x / (double)WIDTH - 1;
// 		double ray_dir_x = game->player_dir_x + game->player_plane_x * camera_x;
// 		double ray_dir_y = game->player_dir_y + game->player_plane_y * camera_x;

// 		int map_x = (int)game->player_pos_x;
// 		int map_y = (int)game->player_pos_y;

// 		double delta_dist_x = fabs(1 / ray_dir_x);
// 		double delta_dist_y = fabs(1 / ray_dir_y);

// 		double side_dist_x;
// 		double side_dist_y;

// 		int step_x;
// 		int step_y;
// 		int hit = 0;
// 		int side;

// 		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (game->player_pos_x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - game->player_pos_x) * delta_dist_x;
// 		}
// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (game->player_pos_y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - game->player_pos_y) * delta_dist_y;
// 		}

// 		while (hit == 0)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			if (game->map[map_y][map_x] == '1')
// 				hit = 1;
// 		}

// 		double perp_wall_dist;
// 		if (side == 0)
// 			perp_wall_dist = (map_x - game->player_pos_x + (1 - step_x) / 2) / ray_dir_x;
// 		else
// 			perp_wall_dist = (map_y - game->player_pos_y + (1 - step_y) / 2) / ray_dir_y;

// 		int line_height = (int)(HEIGHT / perp_wall_dist);

// 		int draw_start = -line_height / 2 + HEIGHT / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		int draw_end = line_height / 2 + HEIGHT / 2;
// 		if (draw_end >= HEIGHT)
// 			draw_end = HEIGHT - 1;

// 		uint32_t color = (side == 1) ? 0xFF5555FF : 0xFF0000FF;

// 		for (int y = draw_start; y <= draw_end; y++)
// 			mlx_put_pixel(game->img, x, y, color);
// 	}
// }
