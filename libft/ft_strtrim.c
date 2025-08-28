/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 16:21:22 by ji-hong           #+#    #+#             */
/*   Updated: 2025/06/10 20:45:01 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chkset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_trimnum(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (ft_chkset(s1[i], set) == 1)
			i ++;
		else
			break ;
	}
	return (i);
}

static int	ft_trimrnum(char const *s1, char const *set, int s1_len)
{
	int	j;

	j = 0;
	while (s1[s1_len - j - 1])
	{
		if (ft_chkset(s1[s1_len - j - 1], set) == 1)
			j ++;
		else
			break ;
	}
	return (j);
}

static char	*ft_rtrnstr(char const *s1, char const *set, int i, int s1_len)
{
	int		j;
	int		str_len;
	char	*str;

	if (i == s1_len)
	{
		j = 0;
		str = (char *)malloc(1);
		if (str == NULL)
			return (NULL);
		*str = '\0';
		return (str);
	}
	else
		j = ft_trimrnum(s1, set, s1_len);
	str_len = s1_len - i - j;
	str = (char *)malloc(str_len + 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1 + i, str_len);
	str[str_len] = '\0';
	return (str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s1_len;
	int		i;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	if (*s1 == 0 || *set == 0)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	i = ft_trimnum(s1, set);
	str = ft_rtrnstr(s1, set, i, s1_len);
	return (str);
}
