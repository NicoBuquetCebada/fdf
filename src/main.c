/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:52:09 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/18 18:48:17 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	print_map(t_point **map, int size)
{
	int	i;
	int	j;

	i = 0;
	printf("\n\n");
	while (map[i])
	{
		j = 0;
		while (j < size)
		{
			printf("%2d ", map[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int ac, char *av[])
{
	char	*file;
	int		*size;
	t_point	**map;
	int		success;

	if (ac != 2)
		custom_error();
	file = read_file(av[1]);
	map = parser(file);
	size = map_size(file);
	print_map(map, size[0]);
	printf("\nx: %d | y: %d\n", size[0], size[1]);
	success = mlx(map, size);
	free(file);
	free_map(map, size[0]);
	free(size);
	if (!success)
		return (1);
	return (0);
}

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
