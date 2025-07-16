/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:56:58 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/16 15:29:02 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../src/libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 256
# define HEIGHT 256 - 30
# define BPP sizeof(int)

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	char	*color;
}			t_point;

char		*buffer_alloc(void);
char		*buffer_concat(char *old_buf, char *tmp, int total, int bytes);
char		*read_map(int fd);
char		*read_file(char *file);

void		free_point(t_point *point);
void		free_map(t_point **map, int size);
int			*map_size(char *map);
t_point		**map_ini(char *map);
t_point		new_point(int x, int y, int z, char *color);
t_point		**map_parser(char *map);


#endif