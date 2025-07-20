/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:38:10 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/18 22:07:24 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* static void	inc_y(char *map, int *i, int *x, int *y)
{
	if (map[*i] == '\n')
	{
		(*y)++;
		*x = 0;
		(*i)++;
	}
	else if (!map[*i] && map[*i - 1] != '\n')
		(*y)++;
} */

static void	while_wspace_inc(int *i, int *y, int *x, char *map)
{
	while (map[*i] && (map[*i] == ' ' || map[*i] == '\t' || map[*i] == '\n'))
	{
		if (map[*i] == '\n')
		{
			(*y)++;
			*x = 0;
		}
		else if (!map[*i] && map[*i - 1] != '\n')
		{
			(*y)++;
			break ;
		}
		(*i)++;
	}
}

static void	while_not_wspace_inc(int *i, char *map)
{
	while (map[*i] && map[*i] != ' ' && map[*i] != '\t' && map[*i] != '\n')
		(*i)++;
}

/* static t_point	insert_values(int x, int y, char **point_values)
{
	t_point	dst;

	if (!point_values[1])
		dst = new_point(x, y, ft_atoi(point_values[0]), NULL);
	else
		dst = new_point(x, y, ft_atoi(point_values[0]), point_values[1]);
	free(point_values[0]);
	free(point_values);
	return (dst);
} */

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
		dst = new_point(x, y, ft_atoi(str), comma + 1);
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

	dst = map_ini(map, size);
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
		dst[y][x] = parse_values(map + start, i - start, x, y);//insert_values(x, y, ft_split(ft_substr(map, start, i - start), ','));
		x++;
	}
	return (dst);
}
