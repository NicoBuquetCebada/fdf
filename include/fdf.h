/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:56:58 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/22 12:47:55 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../src/libft/libft.h"
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define SCALE 5
# define Z 1
# define WIDTH 1920
# define HEIGHT 1080
# define BPP sizeof(int)

typedef struct s_point
{
	int			x;
	int			y;
	int			z;
	char		*color;
}				t_point;

typedef struct s_map
{
	t_point		**map;
	int			width;
	int			height;
	int			max_z;
	int			yellow;
	int			orange;
	int			red;
	int			scale;
}				t_map;

void			custom_size_error(char *file);
void			custom_map_error(char *file, int *size);
void			ft_error(void);

char			*buffer_alloc(void);
char			*buffer_concat(char *old_buf, char *tmp, int total, int bytes);
char			*read_map(int fd);
char			*read_file(char *file);

void			free_map(t_point **map, int size);
void			while_wspace_inc(int *i, int *y, int *x, char *map);
void			while_not_wspace_inc(int *i, char *map);

int				*map_size(char *map);
t_point			**map_ini(char *map, int *size);
t_point			new_point(int x, int y, int z, char *color);
// void		while_wspace_inc(int *i, char *map);
t_point			**map_parser(char *map, int *size);
int				absolute(int n);

t_map			start_map(char *file);

int				mlx(t_map map);
uint32_t		strtohex(const char *str);
unsigned int	ft_strtoul_hex(const char *str);

#endif