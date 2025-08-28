/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:38:04 by ji-hong           #+#    #+#             */
/*   Updated: 2024/11/16 18:09:25 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int					neg;
	int					i;
	unsigned long long	num;

	num = 0;
	neg = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i ++;
	if (nptr[i] == '+')
		i ++;
	else if (nptr[i] == '-')
	{
		neg = -1;
		i ++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (num > LLONG_MAX && neg == -1)
			return (0);
		else if (num > LLONG_MAX && neg == 1)
			return (-1);
		num = num * 10 + nptr[i++] - '0';
	}
	return (num * neg);
}
