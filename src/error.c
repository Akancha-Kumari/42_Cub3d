/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:03:18 by ji-hong           #+#    #+#             */
/*   Updated: 2025/08/28 18:41:32 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/parse.h"

void	error_exit(char *error_msg)
{
	printf("Error\n%s\n", error_msg);
	exit(EXIT_FAILURE);
}

void	line_exit(t_arena *arena, char *line, char *error_msg)
{
	free(line);
	arena_destroy(arena);
	error_exit(error_msg);
}

void	arena_exit(t_arena *arena, char *error_msg)
{
	arena_destroy(arena);
	error_exit(error_msg);
}
