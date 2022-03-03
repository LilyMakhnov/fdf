/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:28:49 by esivre            #+#    #+#             */
/*   Updated: 2021/12/21 11:28:52 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int argc, char **argv)
{
	t_env	fdf;
	int		**tab;
	t_map	map;

	if (argc != 2)
		quit(1, 0, 0);
	check_map(&map, argv);
	tab = alloc_tab(map.x_size, map.y_size);
	fill_tab(tab, map, argv);
	if (!create_env(&fdf, argv[1]))
	{
		free_tab(tab, map.x_size);
		free_env(&fdf);
		return (0);
	}
	ft_frame(tab, &map);
	draw_map(tab, map, &fdf.img);
	free_tab(tab, map.x_size);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img, 0, 0);
	mlx_key_hook(fdf.win, &key_hook, &fdf);
	mlx_hook(fdf.win, 33, 1L << 17, &quit_mouse, &fdf);
	mlx_loop(fdf.mlx);
	free_env(&fdf);
	return (0);
}
