/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/19 22:27:48 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/22 17:56:27 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	max_z(t_map *dst, t_point **map, int width)
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
			if (map[y][x].z > max_z)
				max_z = map[y][x].z;
			x++;
		}
		y++;
	}
	dst->max_z = max_z;
}

static int	ft_fmin(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

static void	get_scale(t_map *map, int win_w, int win_h)
{
	int	map_w;
	int	map_h;
	int	scale_x;
	int	scale_y;
	
//	printf("\nmap_w: %d | map_h: %d\n", map->width, map->height);
	map_w = (map -> width + map -> height) * 866 / 1000;
	map_h = (map -> width + map -> height) / 2 + map -> max_z;
//	printf("\nmap_w: %d | map_h: %d\n", map_w, map_h);
	if (!map_w)
	map_w = 1;
	if (!map_h)
	map_h = 1;
	scale_x = (win_w * 5 / 10) / map_w;
	scale_y = (win_h * 5 / 10) / map_h;
//	printf("\nmap_w: %d | map_h: %d\n", scale_x, scale_y);
	map -> scale = ft_fmin(scale_x, scale_y);
	if (map -> scale < 1)
		map -> scale = 1;
}

static void normalize_z(t_map *map)
{
	float	factor;
	int		x;
	int		y;
	
	factor = 25.0 / map -> max_z;
	map -> max_z = (int)(map->max_z * factor + 0.5f);
	y = 0;
	while (map -> map[y])
	{
		x = 0;
		while (x < map -> width)
		{
			map -> map[y][x].z = (int)(map->map[y][x].z * factor + 0.5f);
			x++;
		}
		y++;
	}
}

static void get_colors(t_map *map)
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
	get_scale(&dst, WIDTH, HEIGHT);
	normalize_z(&dst);
	get_colors(&dst);
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
