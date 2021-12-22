/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:36:24 by esivre            #+#    #+#             */
/*   Updated: 2021/11/30 17:06:59 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}*/
/*
char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	if (!src)
		return (NULL);
	i = -1;
	dest = malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!dest)
		return (NULL);
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}*/
/*
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dest;
	char	*ret;

	if (!s1 || !s2)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!dest)
		return (NULL);
	ret = dest;
	while (*s1)
		*dest++ = *s1++;
	while (*s2)
		*dest++ = *s2++;
	*dest = 0;
	return (ret);
}*/

char	*ft_strduptochar(char *str, char a, size_t n)
{
	char	*dest;
	char	*ret;
	size_t	i;

	i = 0;
	while (str[i] != a && i < n)
		i++;
	dest = malloc(i + 1);
	if (!dest)
		return (NULL);
	ret = dest;
	while (*str != a && n--)
		*dest++ = *str++;
	*dest = 0;
	return (ret);
}
