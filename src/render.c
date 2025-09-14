#include "../include/cub3d.h"

static void fill_ceiling_floor(t_game *game)
{
	uint32_t *pixels = (uint32_t *)game->img->pixels;
	int total_pixels = WIDTH * HEIGHT;
	int i;

	i = 0;
	while (i < (HEIGHT / 2) * WIDTH)
	{
		pixels[i] = 0xAAAAAAFF; // ceiling
		i++;
	}
	while (i < total_pixels)
	{
		pixels[i] = 0x444444FF; // floor
		i++;
	}
}

static void init_ray(t_game *game, t_ray *ray, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->player_dir_x + game->player_plane_x * ray->camera_x;
	ray->ray_dir_y = game->player_dir_y + game->player_plane_y * ray->camera_x;
	ray->map_x = (int)game->player_pos_x;
	ray->map_y = (int)game->player_pos_y;
	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (game->player_pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - game->player_pos_x) * ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (game->player_pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - game->player_pos_y) * ray->delta_dist_y;
	}
}

static void perform_dda(t_game *game, t_ray *ray)
{
	int hit = 0;

	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (game->map[ray->map_y][ray->map_x] == '1')
			hit = 1;
	}

	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - game->player_pos_x + (1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - game->player_pos_y + (1 - ray->step_y) / 2) / ray->ray_dir_y;
}

static mlx_texture_t *select_texture(t_game *game, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->ray_dir_x > 0)
			return (game->tex_west);
		return (game->tex_east);
	}
	if (ray->ray_dir_y > 0)
		return (game->tex_north);
	return (game->tex_south);
}

static void draw_wall_slice(t_game *game, t_ray *ray, mlx_texture_t *texture, int x)
{
	int line_height = (int)(HEIGHT / ray->perp_wall_dist);
	int draw_start = -line_height / 2 + HEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	int draw_end = line_height / 2 + HEIGHT / 2;
	if (draw_end >= HEIGHT)
		draw_end = HEIGHT - 1;

	double wall_x;
	if (ray->side == 0)
		wall_x = game->player_pos_y + ray->perp_wall_dist * ray->ray_dir_y;
	else
		wall_x = game->player_pos_x + ray->perp_wall_dist * ray->ray_dir_x;
	wall_x -= floor(wall_x);

	int tex_x = (int)(wall_x * (double)texture->width);
	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1 && ray->ray_dir_y < 0))
		tex_x = texture->width - tex_x - 1;

	double step = (double)texture->height / line_height;
	double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
	uint32_t *tex_pixels = (uint32_t *)texture->pixels;
	int y;

	y = draw_start;
	while (y <= draw_end)
	{
		int tex_y = (int)tex_pos;
		if (tex_y >= (int)texture->height)
			tex_y = texture->height - 1;
		tex_pos += step;

		uint32_t color = tex_pixels[tex_y * texture->width + tex_x];
		uint8_t b = (color >> 0) & 0xFF;
		uint8_t g = (color >> 8) & 0xFF;
		uint8_t r = (color >> 16) & 0xFF;
		uint8_t a = (color >> 24) & 0xFF;
		if (a == 0)
			a = 0xFF;
		uint32_t fixed_color = (r << 24) | (g << 16) | (b << 8) | a;
		mlx_put_pixel(game->img, x, y, fixed_color);
		y++;
	}
}

void render_frame(void *param)
{
	t_game *game = param;
	int x;
	t_ray ray;
	mlx_texture_t *texture;

	fill_ceiling_floor(game);
	x = 0;
	while (x < WIDTH)
	{
		init_ray(game, &ray, x);
		perform_dda(game, &ray);
		texture = select_texture(game, &ray);
		draw_wall_slice(game, &ray, texture, x);
		x++;
	}
}

// void render_frame(void *param)
// {
// 	t_game *game = param;
// 	uint32_t *pixels = (uint32_t *)game->img->pixels;
// 	int total_pixels = WIDTH * HEIGHT;

// 	// -----------------------------
// 	// 1. Fill ceiling & floor
// 	// -----------------------------
// 	for (int i = 0; i < (HEIGHT / 2) * WIDTH; i++)
// 		pixels[i] = 0xAAAAAAFF; // light gray ceiling
// 	for (int i = (HEIGHT / 2) * WIDTH; i < total_pixels; i++)
// 		pixels[i] = 0x444444FF; // dark gray floor

// 	// -----------------------------
// 	// 2. Raycasting loop
// 	// -----------------------------
// 	for (int x = 0; x < WIDTH; x++)
// 	{
// 		// Camera space
// 		double camera_x = 2 * x / (double)WIDTH - 1;
// 		double ray_dir_x = game->player_dir_x + game->player_plane_x * camera_x;
// 		double ray_dir_y = game->player_dir_y + game->player_plane_y * camera_x;

// 		// Starting grid square
// 		int map_x = (int)game->player_pos_x;
// 		int map_y = (int)game->player_pos_y;

// 		// Delta distances
// 		double delta_dist_x = fabs(1 / ray_dir_x);
// 		double delta_dist_y = fabs(1 / ray_dir_y);

// 		double side_dist_x;
// 		double side_dist_y;
// 		int step_x;
// 		int step_y;
// 		int hit = 0;
// 		int side;

// 		// Calculate step and initial side_dist
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

// 		// -----------------------------
// 		// 3. DDA loop
// 		// -----------------------------
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

// 		// -----------------------------
// 		// 4. Distance to wall
// 		// -----------------------------
// 		double perp_wall_dist;
// 		if (side == 0)
// 			perp_wall_dist = (map_x - game->player_pos_x + (1 - step_x) / 2) / ray_dir_x;
// 		else
// 			perp_wall_dist = (map_y - game->player_pos_y + (1 - step_y) / 2) / ray_dir_y;

// 		// -----------------------------
// 		// 5. Pick texture based on side
// 		// -----------------------------
// 		mlx_texture_t *texture;
// 		if (side == 0)
// 		{
// 			if (ray_dir_x > 0)
// 				texture = game->tex_west;
// 			else
// 				texture = game->tex_east;
// 		}
// 		else
// 		{
// 			if (ray_dir_y > 0)
// 				texture = game->tex_north;
// 			else
// 				texture = game->tex_south;
// 		}

// 		// -----------------------------
// 		// 6. Wall height on screen
// 		// -----------------------------
// 		int line_height = (int)(HEIGHT / perp_wall_dist);

// 		int draw_start = -line_height / 2 + HEIGHT / 2;
// 		if (draw_start < 0)
// 			draw_start = 0;
// 		int draw_end = line_height / 2 + HEIGHT / 2;
// 		if (draw_end >= HEIGHT)
// 			draw_end = HEIGHT - 1;

// 		// -----------------------------
// 		// 7. Texture X coordinate
// 		// -----------------------------
// 		double wall_x;
// 		if (side == 0)
// 			wall_x = game->player_pos_y + perp_wall_dist * ray_dir_y;
// 		else
// 			wall_x = game->player_pos_x + perp_wall_dist * ray_dir_x;
// 		wall_x -= floor(wall_x);

// 		int tex_x = (int)(wall_x * (double)texture->width);
// 		if ((side == 0 && ray_dir_x > 0) || (side == 1 && ray_dir_y < 0))
// 			tex_x = texture->width - tex_x - 1;

// 		// -----------------------------
// 		// 8. Vertical texture mapping
// 		// -----------------------------

// 		double step = (double)texture->height / line_height;
// 		double tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;

// 		uint32_t *tex_pixels = (uint32_t *)texture->pixels;

// 		for (int y = draw_start; y <= draw_end; y++)
// 		{
// 			int tex_y = (int)tex_pos;
// 			if (tex_y >= (int)texture->height)
// 				tex_y = texture->height - 1; // clamp instead of bitmask
// 			tex_pos += step;

// 			uint32_t color = tex_pixels[tex_y * texture->width + tex_x];

// 			// Convert BGRA → RGBA (MLX42 stores pixels as BGRA)
// 			uint8_t b = (color >> 0) & 0xFF;
// 			uint8_t g = (color >> 8) & 0xFF;
// 			uint8_t r = (color >> 16) & 0xFF;
// 			uint8_t a = (color >> 24) & 0xFF;

// 			// Force opaque if you don’t want transparency issues
// 			if (a == 0)
// 				a = 0xFF;
// 			uint32_t fixed_color = (r << 24) | (g << 16) | (b << 8) | a;
// 			mlx_put_pixel(game->img, x, y, fixed_color);
// 		}
// 	}
// }

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
