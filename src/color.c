/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:56:40 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 13:13:32 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	color_parse(const char *str)
{
	uint32_t	color;

	if (!str || str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (0xFFFFFFFF);
	color = (0xFF << 24) | ft_strtoulhex(str);
	return (((color >> 16) << 24) | ((color >> 8 & 0xFF) << 16)
		| ((color & 0xFF) << 8) | 0xFF);
}

uint32_t	getzcolor(t_map map, int z)
{
	if (z > map.red)
		return (0xFF0000FF);
	if (z > map.orange)
		return (0xFFA500FF);
	if (z > map.yellow)
		return (0xFFFF00FF);
	return (0xFFFFFFFF);
}
