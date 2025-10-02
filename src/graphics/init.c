#include "../include/game.h"

// Handles north/south directions
static void set_player_dir_ns(t_game *game, char c)
{
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
}

// Handles east/west directions
static void set_player_dir_ew(t_game *game, char c)
{
	if (c == 'E')
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
}

// Main wrapper function that chooses the correct helper
static void set_player_dir(t_game *game, char c)
{
	if (c == 'N' || c == 'S')
		set_player_dir_ns(game, c);
	else if (c == 'E' || c == 'W')
		set_player_dir_ew(game, c);
}

void init_player(t_game *game)
{
	for (int y = 0; game->map[y]; y++)
	{
		for (int x = 0; game->map[y][x]; x++)
		{
			char c = game->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				game->player_pos_x = x + 0.5;
				game->player_pos_y = y + 0.5;
				set_player_dir(game, c);
				game->map[y][x] = '0';
				return;
			}
		}
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

void init_textures(t_game *game, t_map *map)
{
	game->tex_north = mlx_load_png(map->no);
	game->tex_south = mlx_load_png(map->so);
	game->tex_east = mlx_load_png(map->ea);
	game->tex_west = mlx_load_png(map->we);

	if (!game->tex_north || !game->tex_south || !game->tex_east || !game->tex_west)
		error_exit("Failed to load textures from map file.");
}

// void init_textures(t_game *game)
// {
// 	// Example: four wall textures (N, S, E, W)
// 	game->tex_north = mlx_load_png("./assets/textures/north.png");
// 	game->tex_south = mlx_load_png("./assets/textures/south.png");
// 	game->tex_east = mlx_load_png("./assets/textures/east.png");
// 	game->tex_west = mlx_load_png("./assets/textures/west.png");

// 	if (!game->tex_north || !game->tex_south || !game->tex_east || !game->tex_west)
// 		error_exit("Failed to load textures.");
// }

// void init_player(t_game *game)
// {
// 	int y = 0;
// 	while (game->map[y])
// 	{
// 		int x = 0;
// 		while (game->map[y][x])
// 		{
// 			char c = game->map[y][x];
// 			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
// 			{
// 				game->player_pos_x = x + 0.5;
// 				game->player_pos_y = y + 0.5;

// 				if (c == 'N')
// 				{
// 					game->player_dir_x = 0;
// 					game->player_dir_y = -1;
// 					game->player_plane_x = 0.66;
// 					game->player_plane_y = 0;
// 				}
// 				else if (c == 'S')
// 				{
// 					game->player_dir_x = 0;
// 					game->player_dir_y = 1;
// 					game->player_plane_x = -0.66;
// 					game->player_plane_y = 0;
// 				}
// 				else if (c == 'E')
// 				{
// 					game->player_dir_x = 1;
// 					game->player_dir_y = 0;
// 					game->player_plane_x = 0;
// 					game->player_plane_y = 0.66;
// 				}
// 				else if (c == 'W')
// 				{
// 					game->player_dir_x = -1;
// 					game->player_dir_y = 0;
// 					game->player_plane_x = 0;
// 					game->player_plane_y = -0.66;
// 				}
// 				game->map[y][x] = '0';
// 				return;
// 			}
// 			x++;
// 		}
// 		y++;
// 	}
// }
