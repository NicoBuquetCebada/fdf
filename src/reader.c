/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:10:27 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/18 20:23:31 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#define BUF_SIZE 8192

char	*buffer_alloc(void)
{
	char	*buffer;

	buffer = malloc(1);
	if (!buffer)
		return (NULL);
	buffer[0] = '\0';
	return (buffer);
}

char	*buffer_concat(char *old_buf, char *tmp, int total, int bytes)
{
	char	*new_buf;

	new_buf = malloc(total + bytes + 1);
	if (!new_buf)
		return (NULL);
	for (int i = 0; i < total; i++)
		new_buf[i] = old_buf[i];
	for (int i = 0; i < bytes; i++)
		new_buf[total + i] = tmp[i];
	new_buf[total + bytes] = '\0';
	return (new_buf);
}

char	*read_map(int fd)
{
	char	*buffer;
	char	*new_buf;
	char	tmp[BUF_SIZE + 1];
	int		bytes;
	int		total;

	total = 0;
	buffer = buffer_alloc();
	if (!buffer)
		return (NULL);
	while ((bytes = read(fd, tmp, BUF_SIZE)) > 0)
	{
		tmp[bytes] = '\0';
		new_buf = buffer_concat(buffer, tmp, total, bytes);
		if (!new_buf)
			return (free(buffer), NULL);
		free(buffer);
		buffer = new_buf;
		total += bytes;
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
