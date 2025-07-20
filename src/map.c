/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 22:27:48 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/20 19:56:09 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	max_z(t_point **map, int width)
{
	int	x;
	int y;
	int max_z;

	y = 0;
	max_z = 0;
	while (map[y])
	{
		x = 0;
		while (x < width)
		{
			if (max_z < map[y][x].z)
				max_z = map[y][x].z;
			x++;
		}
		y++;
	}
	return (max_z);
}

static int	ft_fmin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

static void	get_scale(t_map *map, int win_w, int win_h)
{
	int	map_w;
	int	map_h;
	int	scale_x;
	int	scale_y;

	map_w = (map -> width - map -> height) * 866 / 1000;
	map_h = (map -> width + map -> height) * 5 / 10 - map -> max_z;
	scale_x = (win_w * 8 / 10) / map_w;
	scale_y = (win_h * 8 / 10) / map_h;
	map -> scale = ft_fmin(scale_x, scale_y);
	if (map -> scale < 1)
		map -> scale = 1;
}

static t_map	new_map(t_point **map, int width, int height)
{
	t_map	dst;

	dst.map = map;
	dst.width = width;
	dst.height = height;
	dst.max_z = max_z(map, width);
	get_scale(&dst, WIDTH, HEIGHT);
	return (dst);
}

t_map	start_map(char *file)
{
	int		*size;
	t_point **array;
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
