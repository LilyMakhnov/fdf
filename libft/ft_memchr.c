/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:07:02 by esivre            #+#    #+#             */
/*   Updated: 2021/05/21 18:16:20 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*c_s;

	c_s = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (c_s[i] == (unsigned char)c)
			return (&c_s[i]);
		i++;
	}
	return (NULL);
}
