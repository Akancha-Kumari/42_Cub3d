/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:11:19 by ji-hong           #+#    #+#             */
/*   Updated: 2024/11/16 18:31:23 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	num;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		num = n * (-1);
	}
	else
		num = n;
	if (num > 9)
	{
		ft_putnbr_fd(num / 10, fd);
	}
	ft_putchar_fd((num % 10) + '0', fd);
}
