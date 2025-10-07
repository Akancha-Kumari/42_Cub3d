/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:37:38 by akumari           #+#    #+#             */
/*   Updated: 2025/10/06 18:14:00 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// Pack RGB into uint32_t (R << 24 | G << 16 | B << 8 | A)
static uint32_t	rgb_to_uint32(uint8_t r, uint8_t g, uint8_t b)
{
	return ((0xFF << 24) | (b << 16) | (g << 8) | r);
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
			return (game->tex_east);
		return (game->tex_west);
	}
	if (ray->ray_dir_y > 0)
		return (game->tex_south);
	return (game->tex_north);
}

// Pass map for colors
void	render_frame(void *param)
{
	t_game			*game;
	t_ray			ray;
	mlx_texture_t	*texture;
	int				x;

	game = param;
	process_movement(game);
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
