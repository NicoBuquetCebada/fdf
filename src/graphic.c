/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:56:40 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/18 17:09:07 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

/* static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
} */

/* static void	ft_hook(void* param)
{
	const mlx_t* mlx = param;
	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
} */

mlx_t	*start_mlx(void)
{
	mlx_t* mlx;
	
//	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx = mlx_init(WIDTH, HEIGHT, "FDF", false);
	
	if (!mlx)
		return (NULL);
	return (mlx);
}

mlx_image_t	*get_image(mlx_t *mlx, int width, int heigth)
{
	mlx_image_t* img;
	
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

static void	line_draw(int x0, int y0, int x1, int y1, mlx_image_t* img)
{
	int dx;
	int dy;
	int	sx;
	int	sy;
	int err;
	int e2;

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

static void get_iso_x(int x, int y, int *iso_x, int centered_start_x)
{
	x *= SCALE;
	y *= SCALE;
	*iso_x = (x - y) * 866 / 1000 + centered_start_x;
}

static void get_iso_y(int x, int y, int z, int *iso_y, int centered_start_y)
{
	x *= SCALE;
	y *= SCALE;
	z *= 2;
	*iso_y = (x + y) * 5 / 10 - z + centered_start_y;
}

static void get_centered_start(int map_w, int map_h, int map_a, int *cx, int *cy)
{
	map_w *= SCALE;
	map_h *= SCALE;
	map_a *= 2;
	*cx = (map_w - map_h) * 866 / 1000;
	*cy = (map_w + map_h) * 5 / 10 - map_a;
	*cx = (WIDTH - *cx) / 2;
	*cy = (HEIGHT - *cy) / 2;
}

static void isometric_draw(t_point **map, mlx_image_t *img, int map_w, int map_h)
{
	int	x;
	int	y;
	int iso_x0;
	int iso_y0;
	int iso_x1;
	int iso_y1;
	int	centered_start_x;
	int	centered_start_y;

	get_centered_start(map_w - 1, map_h - 1, map[map_h - 1][map_w - 1].z, &centered_start_x, &centered_start_y);
	y = 0;
	while (y < map_h)
	{
		x = 0;
		while (x < map_w - 1)
		{
			get_iso_x(x, y, &iso_x0, centered_start_x);
			get_iso_y(x, y, map[y][x].z, &iso_y0, centered_start_y);
			get_iso_x(x + 1, y, &iso_x1, centered_start_x);
			get_iso_y(x + 1, y, map[y][x + 1].z, &iso_y1, centered_start_y);
			line_draw(iso_x0, iso_y0, iso_x1, iso_y1, img);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < map_w)
	{
		y = 0;
		while (y < map_h - 1)
		{
			get_iso_x(x, y, &iso_x0, centered_start_x);
			get_iso_y(x, y, map[y][x].z, &iso_y0, centered_start_y);
			get_iso_x(x, y + 1, &iso_x1, centered_start_x);
			get_iso_y(x, y + 1, map[y + 1][x].z, &iso_y1, centered_start_y);
			line_draw(iso_x0, iso_y0, iso_x1, iso_y1, img);
			y++;
		}
		x++;
	}
}

int	mlx(t_point **map, int *size)
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	
	mlx = start_mlx();
	if (!mlx)
	return (0);
	img = get_image(mlx, WIDTH, HEIGHT);
	if (!img)
	return (mlx_terminate(mlx), 0);
//	table_draw(size[0] * SCALE, size[1] * SCALE, img);
	isometric_draw(map, img, size[0], size[1]);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}
//mlx_loop_hook(mlx, ft_hook, mlx);	// Register a hook and pass mlx as an optional param.

/* void	center_image(mlx_t *mlx, mlx_image_t *img, int img_w, int img_h)
{
	int	offset_x;
	int offset_y;

	offset_x = (WIDTH - img_w) / 2;
	offset_y = (HEIGHT - img_h) / 2;
	if (mlx_image_to_window(mlx, img, offset_x, offset_y) < 0) {
		mlx_delete_image(mlx, img);
		mlx_terminate(mlx);
		exit(EXIT_FAILURE);
	}
} */