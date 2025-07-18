/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:42:03 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/16 18:06:30 by nbuquet-         ###   ########.fr       */
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

t_point	new_point(int x, int y, int z, char *color)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	point.color = color;
	return (point);
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
			free_point(&map[i][j]);
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
	t_point **dst;
	int *size;
	int i;

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
			return (NULL);
		i++;
	}
	dst[i] = NULL;
	free(size);
	return (dst);
}