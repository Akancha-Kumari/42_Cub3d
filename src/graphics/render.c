/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:37:38 by akumari           #+#    #+#             */
/*   Updated: 2025/10/02 16:48:29 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Pack RGB into uint32_t (R << 24 | G << 16 | B << 8 | A)
static uint32_t	rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

static void	fill_ceiling_floor(t_game *game, t_map *map)
{
	uint32_t	*pixels;
	int			total_pixels;
	int			i;
	uint32_t	ceiling_color;
	uint32_t	floor_color;

	pixels = (uint32_t *)game->img->pixels;
	total_pixels = WIDTH * HEIGHT;
	ceiling_color = rgb_to_uint32(map->c[0], map->c[1], map->c[2]);
	floor_color = rgb_to_uint32(map->f[0], map->f[1], map->f[2]);
	i = 0;
	while (i < (HEIGHT / 2) * WIDTH)
	{
		pixels[i] = ceiling_color;
		i++;
	}
	while (i < total_pixels)
	{
		pixels[i] = floor_color;
		i++;
	}
}

static mlx_texture_t	*select_texture(t_game *game, t_ray *ray)
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

// Pass map for colors
void	render_frame(void *param)
{
	t_game			*game;
	t_ray			ray;
	mlx_texture_t	*texture;
	int				x;

	game = param;
	fill_ceiling_floor(game, game->map_struct);
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
// static void fill_ceiling_floor(t_game *game)
// {
// 	uint32_t *pixels = (uint32_t *)game->img->pixels;
// 	int total_pixels = WIDTH * HEIGHT;
// 	int i;

// 	i = 0;
// 	while (i < (HEIGHT / 2) * WIDTH)
// 	{
// 		pixels[i] = 0xAAAAAAFF; // ceiling
// 		i++;
// 	}
// 	while (i < total_pixels)
// 	{
// 		pixels[i] = 0x444444FF; // floor
// 		i++;
// 	}
// }

// // // static void	init_ray(t_game *game, t_ray *ray, int x)
// // // {
// // // 	ray->camera_x = 2 * x / (double)WIDTH - 1;
// // // 	ray->ray_dir_x = game->player_dir_x + game->player_plane_x
// 		* ray->camera_x;
// // // 	ray->ray_dir_y = game->player_dir_y + game->player_plane_y
// 		* ray->camera_x;
// // // 	ray->map_x = (int)game->player_pos_x;
// // // 	ray->map_y = (int)game->player_pos_y;
// // // 	ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
// // // 	ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
// // // 	if (ray->ray_dir_x < 0)
// // // 	{
// // // 		ray->step_x = -1;
// // // 		ray->side_dist_x = (game->player_pos_x - ray->map_x)
// // 			* ray->delta_dist_x;
// // // 	}
// // // 	else
// // // 	{
// // // 		ray->step_x = 1;
// // // 		ray->side_dist_x = (ray->map_x + 1.0 - game->player_pos_x)
// // 			* ray->delta_dist_x;
// // // 	}
// // // 	if (ray->ray_dir_y < 0)
// // // 	{
// // // 		ray->step_y = -1;
// // // 		ray->side_dist_y = (game->player_pos_y - ray->map_y)
// // 			* ray->delta_dist_y;
// // // 	}
// // // 	else
// // // 	{
// // // 		ray->step_y = 1;
// // // 		ray->side_dist_y = (ray->map_y + 1.0 - game->player_pos_y)
// // 			* ray->delta_dist_y;
// // // 	}
// // }

// static void	perform_dda(t_game *game, t_ray *ray)
// {
// 	int	hit;

// 	hit = 0;
// 	while (hit == 0)
// 	{
// 		if (ray->side_dist_x < ray->side_dist_y)
// 		{
// 			ray->side_dist_x += ray->delta_dist_x;
// 			ray->map_x += ray->step_x;
// 			ray->side = 0;
// 		}
// 		else
// 		{
// 			ray->side_dist_y += ray->delta_dist_y;
// 			ray->map_y += ray->step_y;
// 			ray->side = 1;
// 		}
// 		if (game->map[ray->map_y][ray->map_x] == '1')
// 			hit = 1;
// 	}
// 	if (ray->side == 0)
// 		ray->perp_wall_dist = (ray->map_x - game->player_pos_x + (1
// 					- ray->step_x) / 2) / ray->ray_dir_x;
// 	else
// 		ray->perp_wall_dist = (ray->map_y - game->player_pos_y + (1
// 					- ray->step_y) / 2) / ray->ray_dir_y;
// }

// static void	draw_wall_slice(t_game *game, t_ray *ray,
// mlx_texture_t *texture,
// 		int x)
// {
// 	int			line_height;
// 	int			draw_start;
// 	int			draw_end;
// 	double		wall_x;
// 	int			tex_x;
// 	double		step;
// 	double		tex_pos;
// 	uint32_t	*tex_pixels;
// 	int			y;
// 	int			tex_y;
// 	uint32_t	color;
// 	uint8_t		b;
// 	uint8_t		g;
// 	uint8_t		r;
// 	uint8_t		a;
// 	uint32_t	fixed_color;

// 	line_height = (int)(HEIGHT / ray->perp_wall_dist);
// 	draw_start = -line_height / 2 + HEIGHT / 2;
// 	if (draw_start < 0)
// 		draw_start = 0;
// 	draw_end = line_height / 2 + HEIGHT / 2;
// 	if (draw_end >= HEIGHT)
// 		draw_end = HEIGHT - 1;
// 	if (ray->side == 0)
// 		wall_x = game->player_pos_y + ray->perp_wall_dist * ray->ray_dir_y;
// 	else
// 		wall_x = game->player_pos_x + ray->perp_wall_dist * ray->ray_dir_x;
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * (double)texture->width);
// 	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
// 			&& ray->ray_dir_y < 0))
// 		tex_x = texture->width - tex_x - 1;
// 	step = (double)texture->height / line_height;
// 	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
// 	tex_pixels = (uint32_t *)texture->pixels;
// 	y = draw_start;
// 	while (y <= draw_end)
// 	{
// 		tex_y = (int)tex_pos;
// 		if (tex_y >= (int)texture->height)
// 			tex_y = texture->height - 1;
// 		tex_pos += step;
// 		color = tex_pixels[tex_y * texture->width + tex_x];
// 		b = (color >> 0) & 0xFF;
// 		g = (color >> 8) & 0xFF;
// 		r = (color >> 16) & 0xFF;
// 		a = (color >> 24) & 0xFF;
// 		if (a == 0)
// 			a = 0xFF;
// 		fixed_color = (r << 24) | (g << 16) | (b << 8) | a;
// 		mlx_put_pixel(game->img, x, y, fixed_color);
// 		y++;
// 	}
// }
