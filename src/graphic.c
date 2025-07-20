/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:56:40 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/20 19:56:50 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

mlx_t	*start_mlx(void)
{
	mlx_t	*mlx;

	//	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
	if (!mlx)
		return (NULL);
	return (mlx);
}

mlx_image_t	*get_image(mlx_t *mlx, int width, int heigth)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, width, heigth);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (NULL);
	return (img);
}

static int	absolute(int n)
{
	if (n > 0)
		return (n);
	return (n * -1);
}

static int	direction(int c0, int c1)
{
	if (c0 < c1)
		return (1);
	return (-1);
}

static void	line_draw(int x0, int y0, int x1, int y1, mlx_image_t *img)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = absolute(x1 - x0);
	dy = absolute(y1 - y0);
	sx = direction(x0, x1);
	sy = direction(y0, y1);
	err = dx - dy;
	while (x0 != x1 || y0 != y1)
	{
		mlx_put_pixel(img, x0, y0, 0xFFFFFFFF);
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

static void	get_iso_x(int x, int y, int *iso_x, int centered_start_x)
{
	x *= SCALE;
	y *= SCALE;
	*iso_x = (x - y) * 866 / 1000 + centered_start_x;
}

static void	get_iso_y(int x, int y, int z, int *iso_y, int centered_start_y)
{
	x *= SCALE;
	y *= SCALE;
	z *= Z;
	*iso_y = (x + y) * 5 / 10 - z + centered_start_y;
}

static void	get_centered_start(int map_w, int map_h, int map_a, int *cx,
		int *cy)
{
	map_w *= SCALE;
	map_h *= SCALE;
	map_a *= Z;
	*cx = (map_w - map_h) * 866 / 1000;
	*cy = (map_w + map_h) * 5 / 10 - map_a;
	*cx = (WIDTH - *cx) / 2;
	*cy = (HEIGHT - *cy) / 2;
}

static void	isometric_draw(t_map map, mlx_image_t *img)
{
	int	x;
	int	y;
	int	iso_x0;
	int	iso_y0;
	int	iso_x1;
	int	iso_y1;
	int	centered_start_x;
	int	centered_start_y;

	get_centered_start(map.width - 1, map.height - 1, map.max_z,
		&centered_start_x, &centered_start_y);
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width - 1)
		{
			get_iso_x(x, y, &iso_x0, centered_start_x);
			get_iso_y(x, y, map.map[y][x].z, &iso_y0, centered_start_y);
			get_iso_x(x + 1, y, &iso_x1, centered_start_x);
			get_iso_y(x + 1, y, map.map[y][x + 1].z, &iso_y1, centered_start_y);
			line_draw(iso_x0, iso_y0, iso_x1, iso_y1, img);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < map.width)
	{
		y = 0;
		while (y < map.height - 1)
		{
			get_iso_x(x, y, &iso_x0, centered_start_x);
			get_iso_y(x, y, map.map[y][x].z, &iso_y0, centered_start_y);
			get_iso_x(x, y + 1, &iso_x1, centered_start_x);
			get_iso_y(x, y + 1, map.map[y + 1][x].z, &iso_y1, centered_start_y);
			line_draw(iso_x0, iso_y0, iso_x1, iso_y1, img);
			y++;
		}
		x++;
	}
}

int	mlx(t_map map)
{
	mlx_t		*mlx;
	mlx_image_t	*img;

	mlx = start_mlx();
	if (!mlx)
		return (0);
	img = get_image(mlx, WIDTH, HEIGHT);
	if (!img)
		return (mlx_terminate(mlx), 0);
	isometric_draw(map, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}
