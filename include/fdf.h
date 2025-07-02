/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 11:56:58 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/02 14:06:04 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WIDTH 256
# define HEIGHT 256 - 30
# define BPP sizeof(int)

char		*buffer_alloc(void);
char		*buffer_concat(char *old_buf, char *tmp, int total, int bytes);
char		*read_map(int fd);
char		*read_file(char *file);

int			*map_size(char	*map);

typedef struct s_point
{
	int		x;
	int		y;
	int		z;
	char	*color;
}			t_point;

#endif