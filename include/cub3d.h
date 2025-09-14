#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600
#define MOVE_SPEED 0.1
#define ROT_SPEED 0.05

typedef struct s_game
{
	mlx_t *mlx;
	mlx_image_t *img;
	double player_pos_x;
	double player_pos_y;
	double player_dir_x;
	double player_dir_y;
	double player_plane_x;
	double player_plane_y;
	char **map; // map_grid

	mlx_texture_t *tex_north;
	mlx_texture_t *tex_south;
	mlx_texture_t *tex_east;
	mlx_texture_t *tex_west;
} t_game;

typedef struct s_ray
{
	double ray_dir_x;
	double ray_dir_y;
	double camera_x;
	int map_x;
	int map_y;
	double delta_dist_x;
	double delta_dist_y;
	double side_dist_x;
	double side_dist_y;
	int step_x;
	int step_y;
	int side;
	double perp_wall_dist;
} t_ray;

void error_exit(const char *msg);
void init_textures(t_game *game);
void init_graphics(t_game *game);
void init_player(t_game *game);

void key_hook(mlx_key_data_t keydata, void *param);
void render_frame(void *param);

#endif
