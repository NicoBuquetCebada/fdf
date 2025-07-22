/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoulhex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 20:04:38 by nbuquet-          #+#    #+#             */
/*   Updated: 2025/07/22 20:05:05 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strtoulhex(const char *str)
{
	unsigned int	result;
	int				i;
	char			c;
	unsigned int	digit;

	result = 0;
	i = 0;
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		i = 2;
	while (str[i])
	{
		c = str[i];
		if (c >= '0' && c <= '9')
			digit = c - '0';
		else if (c >= 'a' && c <= 'f')
			digit = 10 + (c - 'a');
		else if (c >= 'A' && c <= 'F')
			digit = 10 + (c - 'A');
		else
			break ;
		result = (result << 4) | digit;
		i++;
	}
	return (result);
}
