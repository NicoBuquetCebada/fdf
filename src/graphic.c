/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:56:40 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/22 20:05:21 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
static int	direction(int c0, int c1)
{
	if (c0 < c1)
		return (1);
	return (-1);
}

static void	line_draw(int x0, int y0, int x1, int y1, mlx_image_t *img,
		uint32_t color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = ft_absolute(x1 - x0);
	dy = ft_absolute(y1 - y0);
	sx = direction(x0, x1);
	sy = direction(y0, y1);
	err = dx - dy;
	while (x0 != x1 || y0 != y1)
	{
		mlx_put_pixel(img, x0, y0, color); // 0xFFFFFFFF
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
	*iso_x = (x - y) * 866 / 1000 + centered_start_x;
}

static void	get_iso_y(int x, int y, int z, int *iso_y, int centered_start_y)
{
	*iso_y = (x + y) / 2 - z + centered_start_y;
}

static void	get_centered_start(int map_w, int map_h, int map_a, int *cx,
		int *cy)
{
	*cx = (map_w - map_h) * 866 / 1000;
	*cy = (map_w + map_h) / 2 - map_a;
	*cx = (WIDTH - *cx) / 2;
	*cy = (HEIGHT - *cy) / 2;
}

uint32_t	strtohex(const char *str)
{
	uint32_t	color;

	if (!str || str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (0xFFFFFFFF);
	color = (0xFF << 24) | ft_strtoulhex(str);
	return (((color >> 16) << 24) | ((color >> 8 & 0xFF) << 16) | ((color & 0xFF) << 8) | 0xFF);
}

static uint32_t	getzcolor(t_map map, int z)
{
	if (z > map.red)
		return (0xFF0000FF);
	if (z > map.orange)
		return (0xFFA500FF);
	if (z > map.yellow)
		return (0xFFFF00FF);
	return (0xFFFFFFFF);
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

	get_centered_start((map.width - 1) * map.scale, (map.height - 1)
		* map.scale, map.max_z, &centered_start_x, &centered_start_y);
	y = 0;
	while (y < map.height)
	{
		x = 0;
		while (x < map.width - 1)
		{
			get_iso_x(x * map.scale, y * map.scale, &iso_x0, centered_start_x);
			get_iso_y(x * map.scale, y * map.scale, map.map[y][x].z, &iso_y0,
				centered_start_y);
			get_iso_x((x + 1) * map.scale, y * map.scale, &iso_x1,
				centered_start_x);
			get_iso_y((x + 1) * map.scale, y * map.scale, map.map[y][x + 1].z,
				&iso_y1, centered_start_y);
			if (map.map[y][x].color)
				line_draw(iso_x0, iso_y0, iso_x1, iso_y1, img,
					strtohex(map.map[y][x].color));
			else
				line_draw(iso_x0, iso_y0, iso_x1, iso_y1, img, getzcolor(map, map.map[y][x].z));
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
			get_iso_x(x * map.scale, y * map.scale, &iso_x0, centered_start_x);
			get_iso_y(x * map.scale, y * map.scale, map.map[y][x].z, &iso_y0,
				centered_start_y);
			get_iso_x(x * map.scale, (y + 1) * map.scale, &iso_x1,
				centered_start_x);
			get_iso_y(x * map.scale, (y + 1) * map.scale, map.map[y + 1][x].z,
				&iso_y1, centered_start_y);
			if (map.map[y][x].color)
				line_draw(iso_x0, iso_y0, iso_x1, iso_y1, img,
					strtohex(map.map[y][x].color));
			else
				line_draw(iso_x0, iso_y0, iso_x1, iso_y1, img, getzcolor(map, map.map[y][x].z));
			y++;
		}
		x++;
	}
}

static void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
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
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}
