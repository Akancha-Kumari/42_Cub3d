/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:38:54 by akumari           #+#    #+#             */
/*   Updated: 2025/10/06 16:27:01 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "parse.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 1280
# define HEIGHT 960
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.05

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	double			player_pos_x;
	double			player_pos_y;
	double			player_dir_x;
	double			player_dir_y;
	double			player_plane_x;
	double			player_plane_y;
	char			**map;
	t_map			*map_struct;
	mlx_texture_t	*tex_north;
	mlx_texture_t	*tex_south;
	mlx_texture_t	*tex_east;
	mlx_texture_t	*tex_west;
}					t_game;

typedef struct s_ray
{
	double			ray_dir_x;
	double			ray_dir_y;
	double			camera_x;
	int				map_x;
	int				map_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			side_dist_x;
	double			side_dist_y;
	int				step_x;
	int				step_y;
	int				side;
	double			perp_wall_dist;
}					t_ray;

typedef struct s_tex_info
{
	int				tex_x;
	double			step;
	double			pos;
}					t_tex_info;

typedef struct s_line_info
{
	int				draw_start;
	int				draw_end;
	int				tex_x;
	t_tex_info		tex;
	mlx_texture_t	*texture;
}					t_line_info;

typedef struct s_line_range
{
	int				height;
	int				start;
	int				end;
}					t_line_range;

typedef struct s_tex_calc
{
	t_game			*game;
	t_ray			*ray;
	mlx_texture_t	*texture;
	int				line_height;
	int				draw_start;
}					t_tex_calc;

void				set_player_dir(t_game *game, char c);
void				init_ray(t_game *game, t_ray *ray, int x);
void				perform_dda(t_game *game, t_ray *ray);
void				draw_wall_slice(t_game *game, t_ray *ray,
						mlx_texture_t *texture, int x);

// void init_textures(t_game *game);
void				init_textures(t_game *game, t_map *map);
void				init_graphics(t_game *game);
void				init_player(t_game *game);

void				key_hook(mlx_key_data_t keydata, void *param);
void				render_frame(void *param);
void				cleanup_game(t_game *game);
void				error_exit_graphic(char *msg, t_game *game, t_map *map);

#endif
