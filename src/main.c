/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:52:09 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/22 12:20:51 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void debug_color(uint32_t color) {
    printf("A:%02X B:%02X G:%02X R:%02X\n",
        (color >> 24) & 0xFF,
        (color >> 16) & 0xFF,
        (color >> 8) & 0xFF,
        color & 0xFF
    );
}

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
			debug_color(strtohex(map[i][j].color));
			j++;
		}
		printf("\n");
		i++;
	}
}

int	main(int ac, char *av[])
{
	char	*file;
	t_map	map;

	if (ac != 2)
		ft_error();
	file = read_file(av[1]);
	map = start_map(file);
	
// 	print_map(map.map, map.width);
	printf("\nx: %d | y: %d | scale: %d\n", map.width, map.height, map.scale);
	
	mlx(map);
	free(file);
	free_map(map.map, map.width);
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
