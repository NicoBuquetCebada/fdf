/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 12:55:37 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 12:56:18 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	direction(int c0, int c1)
{
	if (c0 < c1)
		return (1);
	return (-1);
}

static void	line_draw(int iso[2], int ison[2], mlx_image_t *img, uint32_t color)
{
	int	d[2];
	int	s[2];
	int	err;
	int	e2;

	d[0] = ft_absolute(ison[0] - iso[0]);
	d[1] = ft_absolute(ison[1] - iso[1]);
	s[0] = direction(iso[0], ison[0]);
	s[1] = direction(iso[1], ison[1]);
	err = d[0] - d[1];
	while (iso[0] != ison[0] || iso[1] != ison[1])
	{
		mlx_put_pixel(img, iso[0], iso[1], color);
		e2 = 2 * err;
		if (e2 > -d[1])
		{
			err -= d[1];
			iso[0] += s[0];
		}
		if (e2 < d[0])
		{
			err += d[0];
			iso[1] += s[1];
		}
	}
}

static void	draw_y(t_map map, mlx_image_t *img, int offset[2])
{
	int	y;
	int	x;
	int	iso[2];
	int	ison[2];

	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width - 1)
		{
			iso[0] = get_iso_x(x * map.scale, y * map.scale, offset[0]);
			iso[1] = get_iso_y(x * map.scale, y * map.scale, map.map[y][x].z,
					offset[1]);
			ison[0] = get_iso_x((x + 1) * map.scale, y * map.scale, offset[0]);
			ison[1] = get_iso_y((x + 1) * map.scale, y * map.scale, map.map[y][x
					+ 1].z, offset[1]);
			if (map.map[y][x].color)
				line_draw(iso, ison, img, color_parse(map.map[y][x].color));
			else
				line_draw(iso, ison, img, getzcolor(map, map.map[y][x].z));
			x++;
		}
		y++;
	}
}

static void	draw_x(t_map map, mlx_image_t *img, int offset[2])
{
	int	y;
	int	x;
	int	iso[2];
	int	ison[2];

	x = 0;
	while (x < map.width)
	{
		y = 0;
		while (y < map.height - 1)
		{
			iso[0] = get_iso_x(x * map.scale, y * map.scale, offset[0]);
			iso[1] = get_iso_y(x * map.scale, y * map.scale, map.map[y][x].z,
					offset[1]);
			ison[0] = get_iso_x(x * map.scale, (y + 1) * map.scale, offset[0]);
			ison[1] = get_iso_y(x * map.scale, (y + 1) * map.scale, map.map[y
					+ 1][x].z, offset[1]);
			if (map.map[y][x].color)
				line_draw(iso, ison, img, color_parse(map.map[y][x].color));
			else
				line_draw(iso, ison, img, getzcolor(map, map.map[y][x].z));
			y++;
		}
		x++;
	}
}

void	draw_map(t_map map, mlx_image_t *img)
{
	int	offset[2];

	get_offset(map, offset);
	draw_y(map, img, offset);
	draw_x(map, img, offset);
}
