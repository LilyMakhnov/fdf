/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:11:00 by esivre            #+#    #+#             */
/*   Updated: 2021/12/21 11:24:28 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_line_low(t_data *data, t_point pt0, t_point pt1, t_map map)
{
	int		delta;
	int		x;
	int		y;
	float	dist;

	delta = 2 * abs((int)pt1.y - (int)pt0.y) - (pt1.x - pt0.x);
	y = pt0.y;
	x = pt0.x;
	while (x < pt1.x)
	{
		dist = ft_dist(pt0.x, x, pt0.y, y);
		ft_mlx_pixel_put(data, x, y, color_z(pt0, pt1, map, dist));
		if (delta > 0)
		{
			if (pt1.y > pt0.y)
				y++;
			else
				y--;
			delta += 2 * (abs((int)pt1.y - (int)pt0.y) - (pt1.x - pt0.x));
		}
		else
			delta += 2 * abs((int)pt1.y - (int)pt0.y);
		x++;
	}
}

void	plot_line_high(t_data *data, t_point pt0, t_point pt1, t_map map)
{
	int		delta;
	int		x;
	int		y;
	float	dist;

	delta = 2 * abs((int)pt1.x - (int)pt0.x) - (pt1.y - pt0.y);
	x = pt0.x;
	y = pt0.y;
	while (y < pt1.y)
	{
		dist = ft_dist(pt0.x, x, pt0.y, y);
		ft_mlx_pixel_put(data, x, y, color_z(pt0, pt1, map, dist));
		if (delta > 0)
		{
			if (pt1.x > pt0.x)
				x++;
			else
				x--;
			delta += 2 * (abs((int)pt1.x - (int)pt0.x) - (pt1.y - pt0.y));
		}
		else
			delta += 2 * abs((int)pt1.x - (int)pt0.x);
		y++;
	}
}

void	drawline(t_data *data, t_point pt0, t_point pt1, t_map map)
{
	if (abs((int)pt1.y - (int)pt0.y) < abs((int)pt1.x - (int)pt0.x))
	{
		if (pt0.x > pt1.x)
			plot_line_low(data, pt1, pt0, map);
		else
			plot_line_low(data, pt0, pt1, map);
	}
	else
	{
		if (pt0.y > pt1.y)
			plot_line_high(data, pt1, pt0, map);
		else
			plot_line_high(data, pt0, pt1, map);
	}
}

void	draw_map(int **tab, t_map map, t_data *img)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map.y_size)
	{
		i = -1;
		while (++i + 1 < map.x_size)
		{
			map.pt1 = set_point(map, tab, i, j);
			map.pt2 = set_point(map, tab, i + 1, j);
			drawline(img, map.pt1, map.pt2, map);
			if (j + 1 < map.y_size)
			{
				map.pt2 = set_point(map, tab, i, j + 1);
				drawline(img, map.pt1, map.pt2, map);
			}
		}
		if (j + 1 < map.y_size)
		{
			map.pt1 = set_point(map, tab, i, j);
			map.pt2 = set_point(map, tab, i, j + 1);
			drawline(img, map.pt1, map.pt2, map);
		}
	}
}
