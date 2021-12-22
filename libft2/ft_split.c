/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:18:56 by esivre            #+#    #+#             */
/*   Updated: 2021/05/22 17:01:14 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_copy(char *dest, int *i, const char *str, char c)
{
	int	j;

	j = 0;
	while (str[*i] == c && str[*i])
		(*i)++;
	while (str[*i] != c && str[*i])
	{
		dest[j] = str[*i];
		(*i)++;
		j++;
	}
	dest[j] = 0;
}

static int	sizeword(int *i, const char *str, char c)
{
	int	j;

	j = 0;
	while (str[*i] == c && str[*i])
		(*i)++;
	while (str[*i] != c && str[*i])
	{
		(*i)++;
		j++;
	}
	return (j);
}

static int	count_word(const char *str, char c)
{
	int	i;
	int	isword;
	int	countword;

	i = -1;
	isword = 0;
	countword = 0;
	while (str[++i])
	{
		if (str[i] != c && isword == 0)
		{
			isword = 1;
			countword++;
		}
		if (str[i] == c)
			isword = 0;
	}
	return (countword);
}

static char	**free_split(char **dest, int i)
{
	int	j;

	j = 0;
	while (j < i)
		free(dest[j++]);
	free(dest);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	int		size;
	char	**dest;
	int		i;
	int		pos;

	if (!str)
		return (NULL);
	size = count_word(str, c);
	dest = malloc(sizeof(char *) * (size + 1));
	if (!dest)
		return (NULL);
	i = 0;
	pos = 0;
	while (i < size)
	{
		dest[i] = malloc(sizeof(char) * (sizeword(&pos, str, c) + 1));
		if (!dest[i++])
			return (free_split(dest, i - 1));
	}
	i = 0;
	pos = 0;
	while (i < size)
		ft_copy(dest[i++], &pos, str, c);
	dest[size] = 0;
	return (dest);
}
