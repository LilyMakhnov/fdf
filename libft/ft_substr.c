/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 16:50:46 by esivre            #+#    #+#             */
/*   Updated: 2021/05/22 15:12:47 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	char	*ret;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (len_s < start)
		dest = (char *)malloc(1);
	else if (len_s - start < len)
		dest = (char *)malloc(len_s - start + 1);
	else
		dest = (char *)malloc(len + 1);
	if (!dest)
		return (NULL);
	ret = dest;
	while (*s && start--)
		s++;
	while (*s && len--)
		*dest++ = *s++;
	*dest = 0;
	return (ret);
}
