/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:53:31 by ji-hong           #+#    #+#             */
/*   Updated: 2024/11/14 11:33:09 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*str;

	len = ft_strlen(s);
	str = (char *)malloc(len + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s, len + 1);
	return (str);
}
