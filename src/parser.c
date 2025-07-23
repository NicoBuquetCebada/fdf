/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:38:10 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 11:51:21 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	while_wspace_inc(int *i, int *y, int *x, char *map)
{
	while (map[*i] && (map[*i] == ' ' || map[*i] == '\t' || map[*i] == '\n'))
	{
		if (map[*i] == '\n')
		{
			(*y)++;
			*x = 0;
		}
		(*i)++;
	}
}

static void	while_not_wspace_inc(int *i, char *map)
{
	while (map[*i] && map[*i] != ' ' && map[*i] != '\t' && map[*i] != '\n')
		(*i)++;
}

static t_point	parse_values(char *str, int len, int x, int y)
{
	t_point	dst;
	char	*comma;
	char	t;

	t = str[len];
	str[len] = '\0';
	comma = ft_strchr(str, ',');
	if (comma)
	{
		*comma = '\0';
		dst = new_point(x, y, ft_atoi(str), ft_substr(comma + 1, 0, len));
	}
	else
		dst = new_point(x, y, ft_atoi(str), NULL);
	str[len] = t;
	return (dst);
}

t_point	**map_parser(char *map, int *size)
{
	t_point	**dst;
	int		i;
	int		x;
	int		y;
	int		start;

	dst = map_ini(size);
	if (!dst)
		return (NULL);
	i = 0;
	x = 0;
	y = 0;
	while (map[i])
	{
		while_wspace_inc(&i, &y, &x, map);
		if (!map[i])
			break ;
		start = i;
		while_not_wspace_inc(&i, map);
		dst[y][x] = parse_values(map + start, i - start, x, y);
		x++;
	}
	return (dst);
}
