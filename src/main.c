/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:52:09 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/02 14:06:22 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	main(void) {
	char	*map;
	int		*size;

	map = read_file("./test_maps/42.fdf");
	size = map_size(map);
	printf("\n%s\nsize: %d, %d", map, size[0], size[1]);
}

/* static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

static void ft_hook(void* param)
{
	const mlx_t* mlx = param;

	printf("WIDTH: %d | HEIGHT: %d\n", mlx->width, mlx->height);
}

 int main(void)
{
    // MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "window", false);
	if (!mlx)
		ft_error();


	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Even after the image is being displayed, we can still modify the buffer.
	
	mlx_put_pixel(img, mlx->width/2, mlx->height/2, 0xFF0000FF);
	
	int i = 0;
	while (i < 50) {
		mlx_put_pixel(img, mlx->width/2 + i, mlx->height/2, 0xFF0000FF);
		mlx_put_pixel(img, mlx->width/2, mlx->height/2 + i, 0xFF0000FF);
		i++;
	}
	while (i >= 0) {
		mlx_put_pixel(img, mlx->width/2 + i, mlx->height/2 + 50, 0xFF0000FF);
		mlx_put_pixel(img, mlx->width/2 + 50, mlx->height/2 + i, 0xFF0000FF);
		i--;
	}
	

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
} */

// USE OF COLOR

/* int	main(void)
{
	mlx_t* mlx = mlx_init(256, 256, "MLX42", false);
    if (!mlx)
        exit(EXIT_FAILURE);

    mlx_image_t* img = mlx_new_image(mlx, 128, 128);

    // Set the channels of each pixel in our image to the maximum byte value of 255. 
    memset(img->pixels, 255, img->width * img->height * BPP);

    mlx_image_to_window(mlx, img, 0, 0);

    // Run the main loop and terminate on quit.  
    mlx_loop(mlx);
    mlx_terminate(mlx);
    return (EXIT_SUCCESS);
} */
