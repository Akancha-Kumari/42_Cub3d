/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:54:25 by ji-hong           #+#    #+#             */
/*   Updated: 2025/08/26 13:58:20 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_arena	*arena_create(size_t size)
{
	t_arena	*arena;

	arena = (t_arena *)malloc(sizeof(t_arena));
	if (!arena)
		return (NULL);
	arena->memory = (char *)malloc(size);
	if (!arena->memory)
	{
		free(arena);
		return (NULL);
	}
	arena->offset = 0;
	arena->size = size;
	return (arena);
}

void	*arena_alloc(t_arena *arena, size_t size)
{
	void	*ptr;

	if (arena->offset + size > arena->size)
		return (NULL);
	ptr = arena->memory + arena->offset;
	arena->offset += size;
	return (ptr);
}

char	*arena_strdup(t_arena *arena, const char *s)
{
	int		len;
	char	*str;

	len = ft_strlen(s);
	str = arena_alloc(arena, len + 1);
	if (!str)
		return (NULL);
	ft_memcpy(str, s, len + 1);
	return (str);
}

void	arena_destroy(t_arena *arena)
{
	if (arena)
	{
		free(arena->memory);
		free(arena);
	}
}
