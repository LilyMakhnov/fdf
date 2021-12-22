/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:31:09 by esivre            #+#    #+#             */
/*   Updated: 2021/12/21 11:33:47 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	check_line(int fd, char **line, t_map *map)
{
	char	**parse_line;
	int		i;

	parse_line = ft_split(*line, ' ');
	if (!parse_line)
		quit(1, 0, 0);
	free(*line);
	*line = NULL;
	i = 0;
	while (parse_line[i])
	{
		if (atoi(parse_line[i]) > map->z_max)
			map->z_max = atoi(parse_line[i]);
		if (atoi(parse_line[i]) < map->z_min)
			map->z_min = atoi(parse_line[i]);
		i++;
	}
	free_doublechar(parse_line);
	parse_line = NULL;
	if (!map->x_size)
		map->x_size = i;
	else if (map->x_size != i)
		quit(1, 0, 0);
	(map->y_size)++;
	return (get_next_line(fd, line));
}

void	check_map(t_map *map, char **argv)
{
	int		fd;
	int		gnl;
	char	*line;

	map->x_size = 0;
	map->y_size = 0;
	map->z_min = 0;
	map->z_max = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		quit(1, 0, 0);
	line = NULL;
	gnl = get_next_line(fd, &line);
	while (gnl > 0)
		gnl = check_line(fd, &line, map);
	free(line);
	if (close(fd) || gnl < 0)
		quit(1, 0, 0);
}

int	**alloc_tab(int x_size, int y_size)
{
	int	**tab;
	int	i;

	tab = malloc(sizeof(int *) * x_size);
	if (!tab)
		quit(1, 0, 0);
	i = -1;
	while (++i < x_size)
	{
		tab[i] = malloc(sizeof(int) * y_size);
		if (!tab[i])
		{
			while (i--)
				free(tab[i]);
			free(tab);
			quit(1, 0, 0);
		}
	}
	return (tab);
}

int	fill_xtab(int **tab, int fd, char **line, t_map map)
{
	char		**parse_line;
	static int	j = 0;
	int			i;

	if (j == map.y_size)
		j = 0;
	parse_line = ft_split(*line, ' ');
	free(*line);
	if (!parse_line)
		quit(1, tab, map.x_size);
	i = -1;
	while (++i < map.x_size)
		tab[i][j] = atoi(parse_line[i]);
	free_doublechar(parse_line);
	parse_line = NULL;
	j++;
	return (get_next_line(fd, line));
}

void	fill_tab(int **tab, t_map map, char **argv)
{
	int		fd;
	int		gnl;
	char	*line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		quit(1, 0, 0);
	line = NULL;
	gnl = get_next_line(fd, &line);
	while (gnl > 0)
		gnl = fill_xtab(tab, fd, &line, map);
	free (line);
	if (close(fd) || gnl < 0)
		quit(1, 0, 0);
}
