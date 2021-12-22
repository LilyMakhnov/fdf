/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:38:20 by esivre            #+#    #+#             */
/*   Updated: 2021/11/30 17:07:18 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

# define BUFFER_SIZE 10

char	*ft_strduptochar(char *str, char a, size_t n);
int		ft_strcpychar(char *str, char a);
void	ft_append(char **dest, char *toadd);
int		isinstr(char a, char *str);
int		get_next_line(int fd, char **line);

#endif
