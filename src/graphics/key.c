/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akumari <akumari@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 14:37:24 by akumari           #+#    #+#             */
/*   Updated: 2025/10/06 18:37:04 by akumari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	int		pressed;

	game = param;
	pressed = (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT);
	if (keydata.key == MLX_KEY_ESCAPE && pressed)
		mlx_close_window(game->mlx);
	else if (keydata.key == MLX_KEY_W)
		game->input.w = pressed;
	else if (keydata.key == MLX_KEY_S)
		game->input.s = pressed;
	else if (keydata.key == MLX_KEY_A)
		game->input.a = pressed;
	else if (keydata.key == MLX_KEY_D)
		game->input.d = pressed;
	else if (keydata.key == MLX_KEY_LEFT)
		game->input.left = pressed;
	else if (keydata.key == MLX_KEY_RIGHT)
		game->input.right = pressed;
}
