/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:38:10 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/16 16:43:44 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	while_wspace_inc(int *i, char *map)
{
	while (map[*i] && (map[*i] == ' ' || map[*i] == '\t'))
		(*i)++;
}

static void	while_not_wspace_inc(int *i, char *map)
{
	while (map[*i] && map[*i] != ' ' && map[*i] != '\t' && map[*i] != '\n')
		(*i)++;
}

static void	inc_y(char *map, int *i, int *x, int *y)
{
	if (map[(*i)++] == '\n')
	{
		(*y)++;
		*x = 0;
	}
}

static t_point	insert_values(int x, int y, char **point_values)
{
	t_point	dst;

	if (!point_values[1])
		dst = new_point(x, y, ft_atoi(point_values[0]), NULL);
	else
	{
		dst = new_point(x, y, ft_atoi(point_values[0]), point_values[1]);
		free(point_values[1]);
	}
	free(point_values[0]);
	free(point_values);
	return (dst);
}

t_point	**map_parser(char *map)
{
	t_point	**dst;
	int		i;
	int		x;
	int		y;
	int		start;

	dst = map_ini(map);
	if (!dst)
		return (NULL);
	i = 0;
	x = 0;
	y = 0;
	start = 0;
	while (map[i])
	{
		while_wspace_inc(&i, map);
		start = i;
		while_not_wspace_inc(&i, map);
		dst[y][x] = insert_values(x, y, ft_split(ft_substr(map, start, i
						- start), ','));
		x++;
		inc_y(map, &i, &x, &y);
	}
	return (dst);
}
