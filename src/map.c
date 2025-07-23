/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 22:27:48 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 13:10:46 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	max_z(t_map *dst, t_point **map, int width)
{
	int	x;
	int	y;
	int	max_z;

	y = 0;
	max_z = 0;
	while (map[y])
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x].z > max_z)
				max_z = map[y][x].z;
			x++;
		}
		y++;
	}
	dst->max_z = max_z;
}

static void	get_colors(t_map *map)
{
	int	factor;

	factor = map->max_z / 4;
	map->yellow = factor;
	map->orange = factor * 2;
	map->red = factor * 3;
}

static t_map	new_map(t_point **map, int width, int height)
{
	t_map	dst;

	dst.map = map;
	dst.width = width;
	dst.height = height;
	max_z(&dst, map, width);
	get_scale(&dst, 1920, 1080);
	normalize_z(&dst);
	get_colors(&dst);
	return (dst);
}

t_map	start_map(char *file)
{
	int		*size;
	t_point	**array;
	t_map	map;

	size = map_size(file);
	if (!size)
		custom_size_error(file);
	array = map_parser(file, size);
	if (!array)
		custom_map_error(file, size);
	map = new_map(array, size[0], size[1]);
	free(size);
	return (map);
}
