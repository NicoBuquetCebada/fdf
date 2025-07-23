/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:27 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 13:19:14 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*buffer_alloc(void)
{
	char	*buffer;

	buffer = malloc(1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	return (buffer);
}

static char	*buffer_concat(char *old_buf, char *tmp, int total, int bytes)
{
	char	*new_buf;
	int		i;

	new_buf = malloc(total + bytes + 1);
	if (!new_buf)
		return (NULL);
	i = 0;
	while (i < total)
	{
		new_buf[i] = old_buf[i];
		i++;
	}
	i = 0;
	while (i < bytes)
	{
		new_buf[total + i] = tmp[i];
		i++;
	}
	new_buf[total + bytes] = '\0';
	return (new_buf);
}

static char	*read_map(int fd)
{
	char	*buffer;
	char	*new_buf;
	char	tmp[8192 + 1];
	int		bytes;
	int		total;

	total = 0;
	buffer = buffer_alloc();
	if (!buffer)
		return (NULL);
	bytes = read(fd, tmp, 8192);
	while (bytes > 0)
	{
		tmp[bytes] = '\0';
		new_buf = buffer_concat(buffer, tmp, total, bytes);
		if (!new_buf)
			return (free(buffer), NULL);
		free(buffer);
		buffer = new_buf;
		total += bytes;
		bytes = read(fd, tmp, 8192);
	}
	if (bytes < 0)
		return (perror("Error al leer el archivo"), free(buffer), NULL);
	return (buffer);
}

char	*read_file(char *file)
{
	int		fd;
	char	*map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror("Error al abrir el archivo");
		exit(EXIT_FAILURE);
	}
	map = read_map(fd);
	return (map);
}
