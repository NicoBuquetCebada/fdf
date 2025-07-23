/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scale.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:42:00 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 11:42:40 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_scale(t_map *map, int win_w, int win_h)
{
	int	map_w;
	int	map_h;
	int	scale_x;
	int	scale_y;

	map_w = (map->width + map->height) * 866 / 1000;
	map_h = (map->width + map->height) / 2 + map->max_z;
	if (!map_w)
		map_w = 1;
	if (!map_h)
		map_h = 1;
	scale_x = (win_w * 5 / 10) / map_w;
	scale_y = (win_h * 5 / 10) / map_h;
	map->scale = ft_max(scale_x, scale_y);
	if (map->scale < 1)
		map->scale = 1;
}

void	normalize_z(t_map *map)
{
	float	factor;
	int		x;
	int		y;

	factor = 25.0 / map->max_z;
	map->max_z = (int)(map->max_z * factor + 0.5f);
	y = 0;
	while (map->map[y])
	{
		x = 0;
		while (x < map->width)
		{
			map->map[y][x].z = (int)(map->map[y][x].z * factor + 0.5f);
			x++;
		}
		y++;
	}
}
