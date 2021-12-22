/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:49:15 by esivre            #+#    #+#             */
/*   Updated: 2021/05/22 11:52:12 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_set(char a, char const *set)
{
	while (*set)
	{
		if (a == *set++)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dest;
	char	*ret;
	size_t	size_dest;

	if (!s1 || !set)
		return (NULL);
	if (!(*s1))
		return (ft_strdup((char *)s1));
	size_dest = 0;
	while (*s1 && is_in_set(*s1, set))
		s1++;
	while (*s1++)
		size_dest++;
	s1--;
	while (is_in_set(*--s1, set) && size_dest)
		size_dest--;
	s1 -= size_dest - 1;
	dest = malloc(sizeof(char) * (size_dest + 1));
	if (!dest)
		return (NULL);
	ret = dest;
	while (size_dest--)
		*dest++ = *s1++;
	*dest = 0;
	return (ret);
}
