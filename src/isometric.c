/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:02:21 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 13:10:56 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_offset(t_map map, int offset[2])
{
	int	w;
	int	h;
	int	z;

	w = (map.width - 1) * map.scale;
	h = (map.height - 1) * map.scale;
	z = map.max_z;
	offset[0] = (w - h) * 866 / 1000;
	offset[1] = (w + h) / 2 - z;
	offset[0] = (1920 - offset[0]) / 2;
	offset[1] = (1080 - offset[1]) / 2;
}

int	get_iso_x(int x, int y, int offset_x)
{
	int	iso_x;

	iso_x = (x - y) * 866 / 1000 + offset_x;
	return (iso_x);
}

int	get_iso_y(int x, int y, int z, int offset_y)
{
	int	iso_y;

	iso_y = (x + y) / 2 - z + offset_y;
	return (iso_y);
}
