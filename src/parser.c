/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:38:10 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/16 16:14:25 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_point(t_point *point)
{
	if (point->color)
	{
		free(point->color);
		point->color = NULL;
	}
}

void	free_map(t_point **map, int col)
{
	int	i;
	int	j;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < col)
		{
			if (map[i][j].color)
			{
				free_point(&map[i][j]);
				map[i][j].color = NULL;
			}
			j++;
		}
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

int	*map_size(char *map)
{
	int	*size;
	int	i;

	size = (int *)malloc(2 * sizeof(int));
	if (!size)
		return (NULL);
	size[0] = 0; // x
	size[1] = 0; // y
	i = 0;
	while (map[i])
	{
		while (map[i] && (map[i] == ' ' || map[i] == '\t'))
			i++;
		if (map[i] && map[i] != ' ' && map[i] && '\t' && map[i] != '\n')
		{
			size[0]++;
			while (map[i] && map[i] != ' ' && map[i] != '\t' && map[i] != '\n')
				i++;
		}
		if (map[i++] == '\n')
			size[1]++;
	}
	size[0] /= size[1];
	return (size);
}

t_point	**map_ini(char *map)
{
	t_point	**dst;
	int		*size;
	int		i;

	size = map_size(map);
	if (!size)
		return (NULL);
	dst = malloc((size[1] + 1) * sizeof(t_point *));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size[1])
	{
		dst[i] = malloc((size[0] + 1) * sizeof(t_point));
		if (!dst)
			return (dst[i + 1] = NULL, free_map(dst, size[0]), NULL);
		i++;
	}
	dst[i] = NULL;
	free(size);
	return (dst);
}

t_point	new_point(int x, int y, int z, char *color)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return (point);
}

t_point	**map_parser(char *map)
{
	t_point	**dst;
	int		i;
	int		x;
	int		y;
	int		start;
	char	**vals;

	dst = map_ini(map);
	if (!dst)
		return (NULL);
	i = 0;
	x = 0;
	y = 0;
	start = 0;
	while (map[i])
	{
		while (map[i] && (map[i] == ' ' || map[i] == '\t'))
			i++;
		if (map[i] && map[i] != ' ' && map[i] && '\t' && map[i] != '\n')
		{
			start = i;
			while (map[i] && map[i] != ' ' && map[i] != '\t' && map[i] != '\n')
				i++;
			vals = ft_split(ft_substr(map, start, i - start), ',');
			if (!vals[1])
				dst[y][x] = new_point(x, y, ft_atoi(vals[0]), NULL);
			else
			{
				dst[y][x] = new_point(x, y, ft_atoi(vals[0]), vals[1]);
				free(vals[1]);
			}
			free(vals[0]);
			free(vals);
			x++;
		}
		if (map[i++] == '\n')
		{
			y++;
			x = 0;
		}
	}
	return (dst);
}
