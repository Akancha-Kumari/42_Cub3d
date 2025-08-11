#ifndef CUB3D_H
#define CUB3D_H

#include "MLX42/MLX42.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

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
	double player_angel_x;
	double player_angel_y;
} t_game;

void init_graphics(t_game *game);
void init_player(t_game *game, char **map);

#endif
