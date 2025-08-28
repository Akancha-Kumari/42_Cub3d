/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ji-hong <ji-hong@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 20:46:57 by ji-hong           #+#    #+#             */
/*   Updated: 2025/02/13 20:54:21 by ji-hong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*split_trim(char *s, char c)
{
	int		len;
	char	*p;

	len = ft_strlen(s);
	if (len)
	{
		while (*s == c)
			s ++;
	}
	len = ft_strlen(s);
	if (!len)
	{
		p = (char *)malloc(sizeof(char ) * (len + 1));
		p[len] = 0;
		return (p);
	}
	while (s[len - 1] == c)
		len --;
	p = (char *)malloc(sizeof(char ) * (len + 1));
	if (!p)
		return (NULL);
	ft_memcpy(p, s, len);
	p[len] = 0;
	return (p);
}

static int	word_count(char *s, char c, int *s_len)
{
	int	i;
	int	count;

	count = 1;
	i = 0;
	while (i < *s_len)
	{
		if (s[i] == c)
		{
			s[i] = 0;
			if (s[i + 1] != c)
				count ++;
		}
		i ++;
	}
	return (count);
}

static char	**str_form(char *s, int *s_len, int n)
{
	int		i;
	int		j;
	char	**str;

	str = (char **)malloc(sizeof(char *) * (n + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (i < n && j < *s_len)
	{
		while (!s[j])
			j ++;
		str[i] = s + j;
		while (s[j])
			j ++;
		i ++;
	}
	str[i] = NULL;
	return (str);
}

static char	**str_dup(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_strdup(str[i]);
		if (!str[i])
		{
			i = 0;
			while (str[i])
			{
				free(str[i]);
				i ++;
			}
			free(str);
			return (NULL);
		}
		i ++;
	}
	return (str);
}

char	**ft_split(const char *s, char c)
{
	int		tmp_len;
	int		count;
	char	*tmp;
	char	**str;

	if (!s)
		return (NULL);
	tmp = split_trim((char *)s, c);
	if (!tmp)
		return (NULL);
	tmp_len = ft_strlen(tmp);
	if (tmp_len)
		count = word_count(tmp, c, &tmp_len);
	else
		count = 0;
	str = str_form(tmp, &tmp_len, count);
	if (str)
		str = str_dup(str);
	free (tmp);
	return (str);
}
