/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:39:50 by ji-hong           #+#    #+#             */
/*   Updated: 2024/11/14 11:32:06 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	bsize;
	char	*ptr;

	bsize = nmemb * size;
	if (size && ((bsize / size) != nmemb))
		return (NULL);
	ptr = malloc(bsize);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, bsize);
	return (ptr);
}
