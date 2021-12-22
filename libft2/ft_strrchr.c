/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:47:07 by esivre            #+#    #+#             */
/*   Updated: 2021/05/20 16:49:07 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	size;
	char	*str;

	str = (char *)s;
	size = ft_strlen(s);
	if (c == 0)
		return (&str[size]);
	while (size--)
	{
		if (s[size] == (char)c)
			return (&str[size]);
	}
	return (NULL);
}
