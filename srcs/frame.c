/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:24:54 by esivre            #+#    #+#             */
/*   Updated: 2021/12/21 11:27:19 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	set_point(t_map map, int **tab, int i, int j)
{
	t_point	pnt;

	pnt.x = map.offset_x + x_proj(map, i, j);
	pnt.y = map.offset_y + y_proj(map, i, j, tab[i][j]);
	pnt.x3d = i;
	pnt.y3d = j;
	pnt.z3d = tab[i][j];
	return (pnt);
}

t_offset	shift_offset(int **tab, t_map map)
{
	t_offset	offset;
	int			i;

	map.pt1 = set_point(map, tab, map.x_size - 1, map.y_size - 1);
	offset.x_min = map.pt1.x;
	offset.y_min = map.pt1.y;
	offset.x_max = map.pt1.x;
	offset.y_max = map.pt1.y;
	while (map.y_size-- > 0)
	{	
		i = 0;
		while (i < map.x_size)
		{
			map.pt1 = set_point(map, tab, i++, map.y_size);
			if (map.pt1.x < offset.x_min)
				offset.x_min = map.pt1.x;
			if (map.pt1.y < offset.y_min)
				offset.y_min = map.pt1.y;
			if (map.pt1.x > offset.x_max)
				offset.x_max = map.pt1.x;
			if (map.pt1.y > offset.y_max)
				offset.y_max = map.pt1.y;
		}
	}
	return (offset);
}

void	ft_frame(int **tab, t_map *map)
{
	t_offset	off;

	map->offset_x = WINDOW_WIDTH / 2;
	map->offset_y = WINDOW_HEIGHT / 2;
	map->scale = 1;
	off = shift_offset(tab, *map);
	map->scale = min(WINDOW_WIDTH / (off.x_max - off.x_min),
			WINDOW_HEIGHT / (off.y_max - off.y_min)) * 0.80;
	if (map->scale < 1)
		map->scale = 1;
	off = shift_offset(tab, *map);
	map->offset_x = 2 * map->offset_x - (off.x_max + off.x_min) / 2;
	map->offset_y = 2 * map->offset_y - (off.y_max + off.y_min) / 2;
}
