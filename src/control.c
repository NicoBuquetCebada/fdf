/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 16:47:22 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/16 17:03:08 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	custom_error()
{
	char	*error;
	
	error = strerror(1);
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, error, strlen(error));
    write(STDERR_FILENO, "\n", 1);
    exit(EXIT_FAILURE);
}