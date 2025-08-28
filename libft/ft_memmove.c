/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 10:06:27 by ji-hong           #+#    #+#             */
/*   Updated: 2024/11/12 10:36:46 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;

	if (dest > src)
	{
		d = dest;
		s = (unsigned char *)src;
		while (n--)
			d[n] = s[n];
		return (dest);
	}
	else
		return (ft_memcpy(dest, src, n));
}
