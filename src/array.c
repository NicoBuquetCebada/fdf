/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 11:30:21 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 11:35:50 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_map(t_point **map, int col)
{
	int	i;
	int	j;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (j < col)
		{
			free_point(&map[i][j]);
			j++;
		}
		free(map[i]);
		map[i] = NULL;
		i++;
	}
	free(map);
	map = NULL;
}

t_point	**map_ini(int *size)
{
	t_point	**dst;
	int		i;

	dst = malloc((size[1] + 1) * sizeof(t_point *));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < size[1])
	{
		dst[i] = malloc((size[0] + 1) * sizeof(t_point));
		if (!dst)
			return (NULL);
		i++;
	}
	dst[i] = NULL;
	return (dst);
}

static void	while_wspace(char *map, int *i, int *y)
{
	while (map[*i] && (map[*i] == ' ' || map[*i] == '\t' || map[*i] == '\n'))
	{
		if (map[*i] == '\n')
			(*y)++;
		(*i)++;
	}
}

int	*map_size(char *map)
{
	int	*size;
	int	i;

	size = (int *)malloc(2 * sizeof(int));
	if (!size)
		return (NULL);
	size[0] = 0;
	size[1] = 0;
	i = 0;
	while (map[i])
	{
		while_wspace(map, &i, &size[1]);
		size[0]++;
		while (map[i] && map[i] != ' ' && map[i] != '\t' && map[i] != '\n')
			i++;
		if (!map[i] && map[i - 1] != '\n')
			size[1]++;
	}
	if (size[1] == 0)
		return (free(size), NULL);
	size[0] /= size[1];
	return (size);
}
