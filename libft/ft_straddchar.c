/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_straddchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 15:36:45 by esivre            #+#    #+#             */
/*   Updated: 2021/10/27 16:05:03 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_straddchar(char *str, char c)
{
	char	*ret;
	int		i;

	if (!c)
		return (NULL);
	if (!str)
		return (ft_chartostr(c));
	ret = malloc(ft_strlen(str) + 2);
	if (!ret)
	{
		free(str);
		return (NULL);
	}
	i = -1;
	while (str[++i])
		ret[i] = str[i];
	free(str);
	ret[i++] = c;
	ret[i] = 0;
	return (ret);
}
