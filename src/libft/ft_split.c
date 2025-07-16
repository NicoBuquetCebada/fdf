/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbuquet- <nbuquet-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 23:39:07 by nico              #+#    #+#             */
/*   Updated: 2025/03/06 19:24:49 by nbuquet-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_freearr(char **dst)
{
	size_t	i;

	i = 0;
	while (dst[i])
	{
		free (dst[i]);
		i++;
	}
	free (dst);
	return (dst = NULL);
}

static unsigned int	ft_wrdcnt(const char *s, char c)
{
	size_t	cntr;
	size_t	i;

	i = 0;
	cntr = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			cntr++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (cntr);
}

static char	**ft_splitcpy(char **dst, const char *s,
	unsigned int start, unsigned int end)
{
	unsigned int	len;
	unsigned int	i;

	len = end - start;
	i = 0;
	*dst = (char *)malloc((len + 1) * sizeof(char));
	if (!(*dst))
		return (NULL);
	while (i < len)
	{
		(*dst)[i] = s[start + i];
		i++;
	}
	(*dst)[i] = '\0';
	return (dst);
}

char	**ft_split(char const *s, char c)
{
	char			**dst;
	unsigned int	i;
	unsigned int	start;
	unsigned int	index;

	dst = (char **)malloc((ft_wrdcnt(s, c) + 1) * (sizeof(char *)));
	if (!dst)
		return (free((void *)s), NULL);
	i = 0;
	index = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			start = i;
			while (s[i] != c && s[i])
				i++;
			if (!ft_splitcpy(&dst[index++], s, start, i))
				return (free((void *)s), ft_freearr(dst));
		}
	}
	dst[index] = NULL;
	return (free((void *)s), dst);
}
