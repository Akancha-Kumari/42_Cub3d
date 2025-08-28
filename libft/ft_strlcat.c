/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 16:30:26 by ji-hong           #+#    #+#             */
/*   Updated: 2024/11/13 15:49:09 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	if ((!dst || !src) && size == 0)
		return (0);
	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (len_dst >= size)
		return (len_src + size);
	i = 0;
	while (src[i] && (len_dst + i + 1) < size)
	{
		dst[len_dst + i] = src[i];
		i ++;
	}
	dst[len_dst + i] = '\0';
	return (len_src + len_dst);
}
