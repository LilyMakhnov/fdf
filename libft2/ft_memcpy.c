/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:09:05 by esivre            #+#    #+#             */
/*   Updated: 2021/05/21 18:20:44 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*c_dest;
	char	*c_src;

	if (!dest && !src)
		return (NULL);
	c_dest = (char *)dest;
	c_src = (char *)src;
	while (n--)
		*c_dest++ = *c_src++;
	return (dest);
}
