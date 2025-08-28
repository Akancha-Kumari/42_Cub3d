/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:07:03 by ji-hong           #+#    #+#             */
/*   Updated: 2025/08/25 20:14:20 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parse.h"

int	chk_filename(char *name, char *extension)
{
	int	len;

	len = ft_strlen(name);
	if (len < 4)
		return (1);
	else if (ft_strncmp(name + (len - 4), extension, 4))
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char	*trim_front(char *s)
{
	while (ft_isspace(*s))
		s ++;
	return (s);
}

int	ft_isemptystring(char *s)
{
	s = trim_front(s);
	if (*s)
		return (0);
	return (1);
}

void	trim_rear(char *s)
{
	int	len;

	len = ft_strlen(s);
	while (len > 0)
	{
		if (ft_isspace(s[len - 1]))
			s[len - 1] = 0;
		else
			break ;
		len --;
	}
}
