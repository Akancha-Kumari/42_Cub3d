/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:36:40 by ji-hong           #+#    #+#             */
/*   Updated: 2024/11/14 11:21:31 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n == 0)
		len ++;
	while (n)
	{
		n /= 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		c;
	int		neg;
	char	*str;

	c = ft_numlen(n);
	neg = 1;
	if (n < 0)
	{
		neg = -1;
		c ++;
	}
	str = (char *)malloc(c + 1);
	if (str == NULL)
		return (NULL);
	str[c--] = '\0';
	if (n == 0)
		str[0] = '0';
	while (n)
	{
		str[c--] = n % 10 * neg + '0';
		n /= 10;
	}
	if (neg == -1)
		str[0] = '-';
	return (str);
}
