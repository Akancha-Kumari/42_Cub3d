/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:56:42 by ji-hong           #+#    #+#             */
/*   Updated: 2025/08/26 13:57:39 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H

# include "../libft/libft.h"

# define ARENA_SIZE 10485760

typedef struct s_arena
{
	void	*memory;
	size_t	offset;
	size_t	size;
}	t_arena;

t_arena	*arena_create(size_t size);
void	*arena_alloc(t_arena *arena, size_t size);
char	*arena_strdup(t_arena *arena, const char *s);
void	arena_destroy(t_arena *arena);

#endif
