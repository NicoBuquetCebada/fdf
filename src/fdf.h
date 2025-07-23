/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:56:58 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 14:04:31 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <MLX42/MLX42.h>
# include <fcntl.h>
# include <libft.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	char	*color;
}			t_point;

typedef struct s_map
{
	t_point	**map;
	int		width;
	int		height;
	int		max_z;
	int		yellow;
	int		orange;
	int		red;
	int		scale;
}			t_map;

int			check_file_ext(char *fileno);
void		custom_size_error(char *file);
void		custom_map_error(char *file, int *size);
void		ft_error(void);

char		*read_file(char *file);

t_point		new_point(int x, int y, int z, char *color);
void		free_point(t_point *point);

void		free_map(t_point **map, int size);
t_point		**map_ini(int *size);
int			*map_size(char *map);

t_point		**map_parser(char *map, int *size);

void		get_scale(t_map *map, int win_w, int win_h);
void		normalize_z(t_map *map);

t_map		start_map(char *file);

void		get_offset(t_map map, int offset[2]);
int			get_iso_x(int x, int y, int offset_x);
int			get_iso_y(int x, int y, int z, int offset_y);

uint32_t	color_parse(const char *str);
uint32_t	getzcolor(t_map map, int z);

void		draw_map(t_map map, mlx_image_t *img);

int			mlx(t_map map);

#endif