#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/MLX42.h"
# include "parse.h"
# include <math.h>
# include <string.h>

# define WIDTH 800
# define HEIGHT 600

// I took out some header files.
// They have been included in other header files.
// If there is an issue, then add the necessary ones plz

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	double		player_pos_x;
	double		player_pos_y;
	double		player_dir_x;
	double		player_dir_y;
	double		player_plane_x;
	double		player_plane_y;
	char		**map;
	t_arena		*arena;
}	t_game;
// I have added arena to your struct.
// If you need to exit the program you need to use arena_exit function.
// arena_exit(game->arena, "your error exit message");

#endif
