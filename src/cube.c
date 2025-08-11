#include "../include/cub3d.h"

void init_player(t_game *game, char **map)
{
	int x = 0;
	while (map[x])
	{
		int y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'N' || map[x][y] == 'S' || map[x][y] == 'E' || map[x][y] == 'W')
			{
				game->player_pos_x = x + 0.5;
				game->player_pos_y = y + 0.5;

				if (map[x][y] == 'N')
				{
					game->player_dir_x = 0;
					game->player_dir_y = -1;
					game->player_angel_x = 0.66;
					game->player_angel_y = 0;
				}
				else if (map[x][y] == 'S')
				{
					game->player_dir_x = 0;
					game->player_dir_y = 1;
					game->player_angel_x = -0.66;
					game->player_angel_y = 0;
				}
				else if (map[x][y] == 'E')
				{
					game->player_dir_x = 1;
					game->player_dir_y = 0;
					game->player_angel_x = 0;
					game->player_angel_y = 0.66;
				}
				else if (map[x][y] == 'W')
				{
					game->player_dir_x = -1;
					game->player_dir_y = 0;
					game->player_angel_x = 0;
					game->player_angel_y = -0.66;
				}
				map[x][y] = '0';
				return;
			}
			y++;
		}
		x++;
	}
}

void init_graphics(t_game *game)
{
	game->mlx = mlx_init(WIDTH, HEIGHT, "Cub3d", true);
	if (!game->mlx)
		printf("Failed to initialize MLX.\n");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->img)
		printf("Failed to create image buffer.\n");
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		printf("Failed to display image.\n");
}

int main(void)
{
	t_game game;
	memset(&game, 0, sizeof(t_game));

	char *map[] = {
		"111111",
		"100101",
		"101001",
		"1100N1",
		"111111",
		NULL};
	init_graphics(&game);
	init_player(&game, map);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
// int x = 0;
// while (x < HEIGHT)
// {
// 	int y = 0;
// 	while (y < WIDTH)
// 	{
// 		uint32_t color = 0xFFADD8E6;
// 		mlx_put_pixel(game->img, y, x, color);
// 		y++;
// 	}
// 	x++;
// }
