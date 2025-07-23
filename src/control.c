/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:47:22 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/23 14:04:06 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_file_ext(char *fileno)
{
	char	*dot;

	dot = ft_strrchr(fileno, '.');
	if (!dot)
		return (0);
	if (ft_strncmp(dot + 1, "fdf", 3) != 0)
		return (0);
	return (1);
}

void	custom_map_error(char *file, int *size)
{
	char	*error;

	error = strerror(1);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error, strlen(error));
	write(STDERR_FILENO, "\n", 1);
	free(file);
	free(size);
	exit(EXIT_FAILURE);
}

void	custom_size_error(char *file)
{
	char	*error;

	error = strerror(1);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error, strlen(error));
	write(STDERR_FILENO, "\n", 1);
	free(file);
	exit(EXIT_FAILURE);
}

void	ft_error(void)
{
	char	*error;

	error = strerror(1);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error, strlen(error));
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}
