/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:48:05 by akumari           #+#    #+#             */
/*   Updated: 2025/10/02 16:48:49 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static uint32_t	fix_color(uint32_t color)
{
	uint8_t	b;
	uint8_t	g;
	uint8_t	r;
	uint8_t	a;

	b = (color >> 0) & 0xFF;
	g = (color >> 8) & 0xFF;
	r = (color >> 16) & 0xFF;
	a = (color >> 24) & 0xFF;
	if (a == 0)
		a = 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

static void	draw_vertical(t_game *game, int x, t_line_info *line)
{
	uint32_t	*tex_pixels;
	int			tex_y;
	uint32_t	color;
	uint32_t	fixed_color;
	int			y;

	tex_pixels = (uint32_t *)line->texture->pixels;
	y = line->draw_start;
	while (y <= line->draw_end)
	{
		tex_y = (int)line->tex.pos;
		if (tex_y >= (int)line->texture->height)
			tex_y = line->texture->height - 1;
		line->tex.pos += line->tex.step;
		color = tex_pixels[tex_y * line->texture->width + line->tex_x];
		fixed_color = fix_color(color);
		mlx_put_pixel(game->img, x, y, fixed_color);
		y++;
	}
}

static t_line_range	get_line_range(t_ray *ray)
{
	t_line_range	range;

	range.height = (int)(HEIGHT / ray->perp_wall_dist);
	range.start = -range.height / 2 + HEIGHT / 2;
	if (range.start < 0)
		range.start = 0;
	range.end = range.height / 2 + HEIGHT / 2;
	if (range.end >= HEIGHT)
		range.end = HEIGHT - 1;
	return (range);
}

static t_tex_info	get_texture_info(t_tex_calc c)
{
	t_tex_info	tex;
	double		wall_x;

	if (c.ray->side == 0)
		wall_x = c.game->player_pos_y + c.ray->perp_wall_dist
			* c.ray->ray_dir_y;
	else
		wall_x = c.game->player_pos_x + c.ray->perp_wall_dist
			* c.ray->ray_dir_x;
	wall_x -= floor(wall_x);
	tex.step = (double)c.texture->height / c.line_height;
	tex.pos = (c.draw_start - HEIGHT / 2 + c.line_height / 2) * tex.step;
	tex.tex_x = (int)(wall_x * (double)c.texture->width);
	if ((c.ray->side == 0 && c.ray->ray_dir_x > 0) || (c.ray->side == 1
			&& c.ray->ray_dir_y < 0))
		tex.tex_x = c.texture->width - tex.tex_x - 1;
	return (tex);
}

void	draw_wall_slice(t_game *game, t_ray *ray, mlx_texture_t *texture, int x)
{
	t_line_range	range;
	t_tex_info		tex;
	t_line_info		line;
	t_tex_calc		calc;

	range = get_line_range(ray);
	calc.game = game;
	calc.ray = ray;
	calc.texture = texture;
	calc.line_height = range.height;
	calc.draw_start = range.start;
	tex = get_texture_info(calc);
	line.draw_start = range.start;
	line.draw_end = range.end;
	line.tex_x = tex.tex_x;
	line.tex = tex;
	line.texture = texture;
	draw_vertical(game, x, &line);
}

// void	draw_wall_slice(t_game *game, t_ray *ray, mlx_texture_t *texture, int x)
// {
// 	int			tex_x;
// 	double		step;
// 	double		tex_pos;
// 	uint32_t	*tex_pixels;
// 	int			tex_y;
// 	uint32_t	color;
// 	uint32_t	fixed_color;
// 	int			y;
// 	int			line_height;
// 	int			draw_start;
// 	int			draw_end;

// 	calc_line_range(ray, &line_height, &draw_start, &draw_end);
// 	tex_x = calc_tex_x(game, ray, texture);
// 	*step = (double)texture->height / line_height;
// 	*tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * (*step);
// 	tex_pixels = (uint32_t *)texture->pixels;
// 	y = draw_start;
// 	while (y <= draw_end)
// 	{
// 		tex_y = (int)tex_pos;
// 		if (tex_y >= (int)texture->height)
// 			tex_y = texture->height - 1;
// 		tex_pos += step;
// 		color = tex_pixels[tex_y * texture->width + tex_x];
// 		fixed_color = fix_color(color);
// 		mlx_put_pixel(game->img, x, y, fixed_color);
// 		y++;
// 	}
// }

// void	draw_wall_slice(t_game *game, t_ray *ray, mlx_texture_t *texture, int x)
// {
// 	int			line_height;
// 	int			draw_start;
// 	int			draw_end;
// 	int			tex_x;
// 	t_tex_info	tex;
// 	t_line_info	line;

// 	calc_line_range(ray, &line_height, &draw_start, &draw_end);
// 	tex_x = calc_tex_x(game, ray, texture);
// 	tex = calc_tex_info(line_height, draw_start, texture->height);
// 	line.draw_start = draw_start;
// 	line.draw_end = draw_end;
// 	line.tex_x = tex_x;
// 	line.tex = tex;
// 	line.texture = texture;
// 	draw_vertical(game, x, &line);
// }

// static void	calc_line_range(t_ray *ray, int *line_height, int *draw_start,
// 		int *draw_end)
// {
// 	*line_height = (int)(HEIGHT / ray->perp_wall_dist);
// 	*draw_start = -(*line_height) / 2 + HEIGHT / 2;
// 	if (*draw_start < 0)
// 		*draw_start = 0;
// 	*draw_end = (*line_height) / 2 + HEIGHT / 2;
// 	if (*draw_end >= HEIGHT)
// 		*draw_end = HEIGHT - 1;
// }

// static int	calc_tex_x(t_game *game, t_ray *ray, mlx_texture_t *texture)
// {
// 	double	wall_x;
// 	int		tex_x;

// 	if (ray->side == 0)
// 		wall_x = game->player_pos_y + ray->perp_wall_dist * ray->ray_dir_y;
// 	else
// 		wall_x = game->player_pos_x + ray->perp_wall_dist * ray->ray_dir_x;
// 	wall_x -= floor(wall_x);
// 	tex_x = (int)(wall_x * (double)texture->width);
// 	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
// 			&& ray->ray_dir_y < 0))
// 		tex_x = texture->width - tex_x - 1;
// 	return (tex_x);
// }

// void	draw_wall_slice(t_game *game, t_ray *ray, mlx_texture_t *texture, int x)
// {
// 	t_line_range	range;
// 	t_tex_info	tex;
// 	t_line_info	line;

// 	range = get_line_range(ray);
// 	tex = get_texture_info(game, ray, texture, range.height, range.start);

// 	line.draw_start = range.start;
// 	line.draw_end = range.end;
// 	line.tex_x = tex.tex_x;
// 	line.tex = tex;
// 	line.texture = texture;

// 	draw_vertical(game, x, &line);
// }

// static t_tex_info	get_texture_info(t_game *game, t_ray *ray,
// 		mlx_texture_t *texture, int line_height, int draw_start)
// {
// 	t_tex_info	tex;
// 	double		wall_x;

// 	if (ray->side == 0)
// 		wall_x = game->player_pos_y + ray->perp_wall_dist * ray->ray_dir_y;
// 	else
// 		wall_x = game->player_pos_x + ray->perp_wall_dist * ray->ray_dir_x;
// 	wall_x -= floor(wall_x);
// 	tex.step = (double)texture->height / line_height;
// 	tex.pos = (draw_start - HEIGHT / 2 + line_height / 2) * tex.step;
// 	tex.tex_x = (int)(wall_x * (double)texture->width);
// 	if ((ray->side == 0 && ray->ray_dir_x > 0) || (ray->side == 1
// 			&& ray->ray_dir_y < 0))
// 		tex.tex_x = texture->width - tex.tex_x - 1;
// 	return (tex);
// }