/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 13:55:40 by esivre            #+#    #+#             */
/*   Updated: 2021/12/21 11:45:59 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strcpychar(char *str, char a)
{
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != a)
		i++;
	i++;
	j = 0;
	while (str[i])
		str[j++] = str[i++];
	str[j] = 0;
	return (1);
}

void	ft_append(char **dest, char *toadd)
{
	char	*tmp;

	tmp = ft_strdup(*dest);
	free(*dest);
	*dest = ft_strjoin(tmp, toadd);
	free(tmp);
}

int	isinstr(char a, char *str)
{
	while (*str)
		if (*str++ == a)
			return (1);
	return (0);
}

int	ft_read(int fd, char *buffer)
{
	int	rd;

	rd = read(fd, buffer, BUFFER_SIZE);
	if (rd < 0)
		return (-1);
	buffer[rd] = 0;
	if (rd == 0)
		return (0);
	return (rd);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[12288][BUFFER_SIZE + 1];
	int			rd;
	char		*tmp;

	if (fd < 0 || fd >= 12288 || BUFFER_SIZE <= 0)
		return (-1);
	*line = ft_strdup("");
	if (!buffer[fd][0])
	{
		rd = ft_read(fd, buffer[fd]);
		if (rd <= 0)
			return (rd);
	}
	while (!isinstr('\n', buffer[fd]))
	{
		ft_append(line, buffer[fd]);
		rd = ft_read(fd, buffer[fd]);
		if (rd <= 0)
			return (rd);
	}
	tmp = ft_strduptochar(buffer[fd], '\n', BUFFER_SIZE);
	ft_append(line, tmp);
	free(tmp);
	return (ft_strcpychar(buffer[fd], '\n'));
}
