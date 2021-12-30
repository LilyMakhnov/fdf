/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:29:23 by esivre            #+#    #+#             */
/*   Updated: 2021/12/21 11:29:55 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

float	ft_dist(float x0, float x1, float y0, float y1)
{
	return (sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
}

float	x_proj(t_map map, int x, int y)
{
	float	ret;

	ret = 1.4142 / 2 * ((float)x - (float)y);
	return (map.scale * ret);
}

float	y_proj(t_map map, int x, int y, int z)
{
	float	ret;

	ret = 1.4142 / 1.7321 * (float)y + 1 / 2.4495 * ((float)x - (float)z);
	return (map.scale * ret);
}

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}
