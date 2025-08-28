/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:39:26 by ji-hong           #+#    #+#             */
/*   Updated: 2024/11/14 11:12:21 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str1;
	char	*str2;

	str1 = (char *)s;
	str2 = NULL;
	while (*str1)
	{
		if (*str1 == (unsigned char)c)
			str2 = str1;
		str1 ++;
	}
	if (*str1 == '\0' && (unsigned char)c == '\0')
		return (str1);
	return (str2);
}
