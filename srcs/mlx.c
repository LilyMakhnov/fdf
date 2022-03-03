/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:30:19 by esivre            #+#    #+#             */
/*   Updated: 2021/12/21 17:22:02 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT)
	{
		dst = data->addr
			+ (y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

int	key_hook(int keycode, t_env *param)
{
	if (keycode == 65307)
	{
		mlx_destroy_image (param->mlx, param->img.img);
		mlx_destroy_window (param->mlx, param->win);
		mlx_destroy_display(param->mlx);
		free(param->mlx);
		exit(0);
	}
	return (0);
}

int	quit_mouse(t_env *param)
{
	mlx_destroy_image (param->mlx, param->img.img);
	mlx_destroy_window (param->mlx, param->win);
	mlx_destroy_display(param->mlx);
	free(param->mlx);
	exit(0);
	return (0);
}

int	create_env(t_env *fdf, char *str)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (0);
	fdf->win = mlx_new_window(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, str);
	if (!fdf->win)
		return (0);
	fdf->img.img = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!fdf->img.img)
		return (0);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel,
			&fdf->img.line_length, &fdf->img.endian);
	if (!fdf->img.addr)
		return (0);
	return (1);
}
