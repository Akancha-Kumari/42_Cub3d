/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@studnet.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:54:02 by ji-hong           #+#    #+#             */
/*   Updated: 2025/06/10 20:44:12 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	char	*p;

	little_len = ft_strlen(little);
	p = (char *)big;
	if (*little == '\0')
		return (p);
	while (len && *p)
	{
		if (*p == *little && len >= little_len)
		{
			if (ft_strncmp(p, little, little_len) == 0)
				return (p);
		}
		len --;
		p ++;
	}
	return (NULL);
}
