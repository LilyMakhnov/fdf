/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:27:55 by esivre            #+#    #+#             */
/*   Updated: 2021/12/21 11:28:29 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_tab(int **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
}

void	quit(int a, int **tab, int x_size)
{
	if (tab)
		free_tab(tab, x_size);
	if (a == 1)
	{
		write (2, "Error\n", 6);
		exit(1);
	}
	else
		exit(0);
}

void	free_doublechar(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_env(t_env *fdf)
{
	if (fdf->mlx)
	{
		if (fdf->win)
			mlx_destroy_window (fdf->mlx, fdf->win);
		if (fdf->img.img)
			mlx_destroy_image (fdf->mlx, fdf->img.img);
		mlx_destroy_display(fdf->mlx);
		free(fdf->mlx);
	}
}
