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
	char **map;
} t_game;

#endif
