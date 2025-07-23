/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:54:28 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 13:14:40 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static mlx_t	*start_mlx(void)
{
	mlx_t	*mlx;

	mlx = mlx_init(1920, 1080, "FDF", false);
	if (!mlx)
		return (NULL);
	return (mlx);
}

static mlx_image_t	*get_image(mlx_t *mlx, int width, int heigth)
{
	mlx_image_t	*img;

	img = mlx_new_image(mlx, width, heigth);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		return (NULL);
	return (img);
}

static void	ft_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
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
	img = get_image(mlx, 1920, 1080);
	if (!img)
		return (mlx_terminate(mlx), 0);
	draw_map(map, img);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (1);
}
