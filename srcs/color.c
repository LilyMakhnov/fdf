/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:09:48 by esivre            #+#    #+#             */
/*   Updated: 2021/12/21 11:10:40 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rgb(int red, int green, int blue)
{
	return (red * 0x010000 + green * 0x000100 + blue * 0x000001);
}

unsigned int	ft_hsl(unsigned int i)
{
	i = i % 360;
	if (i < 60)
		return (rgb(255, i * 4.25, 0));
	if (i < 120)
		return (rgb(255 - (i - 60) * 4.25, 255, 0));
	if (i < 180)
		return (rgb(0, 255, (i - 120) * 4.25));
	if (i < 240)
		return (rgb(0, 255 - (i - 180) * 4.25, 255));
	if (i < 300)
		return (rgb((i - 240) * 4.25, 0, 255));
	else
		return (rgb(255, 0, 255 - (i - 300) * 4.25));
}

int	color_z(t_point pt0, t_point pt1, t_map map, float dist)
{
	float	ret;
	float	color;
	float	color_max;

	if (map.z_max != map.z_min)
	{
		color = (pt0.z3d - map.z_min) * 320 / (map.z_max - map.z_min);
		color_max = (pt1.z3d - map.z_min) * 320 / (map.z_max - map.z_min);
		ret = color + dist / ft_dist(pt0.x, pt1.x, pt0.y, pt1.y)
			* (color_max - color);
		return (ft_hsl((int)ret));
	}
	return (ft_hsl(0));
}
