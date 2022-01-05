/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esivre <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 11:47:14 by esivre            #+#    #+#             */
/*   Updated: 2022/01/05 15:29:28 by esivre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "mlx.h"
# include <fcntl.h>
# include <math.h>

// VARIABLES
# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080

// STRUCTS
typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_env
{
	void	*mlx;
	void	*win;
	t_data	img;
}	t_env;

typedef struct s_offset
{
	float	x_min;
	float	y_min;
	float	x_max;
	float	y_max;
}	t_offset;

typedef struct s_point
{
	float	x;
	float	y;
	int		x3d;
	int		y3d;
	int		z3d;
}	t_point;

typedef struct s_map
{
	int			x_size;
	int			y_size;
	int			z_size;
	int			z_max;
	int			z_min;
	float		scale;
	int			offset_x;
	int			offset_y;
	t_offset	offset;
	t_point		pt1;
	t_point		pt2;
}	t_map;

//frame
t_point			set_point(t_map map, int **tab, int i, int j);
t_offset		shift_offset(int **tab, t_map map);
void			ft_frame(int **tab, t_map *map);

//check.c
int				check_line(int fd, char **line, t_map *map);
void			check_map(t_map *map, char **argv);
int				**alloc_tab(int x_size, int y_size);
int				fill_xtab(int **tab, int fd, char **line, t_map map);
void			fill_tab(int **tab, t_map map, char **argv);

//draw.c
void			plot_line_low(t_data *data, t_point pt0,
					t_point pt1, t_map map);
void			plot_line_high(t_data *data, t_point pt0,
					t_point pt1, t_map map);
void			drawline(t_data *data, t_point pt0, t_point pt1, t_map map);
void			draw_map(int **tab, t_map map, t_data *img);

//color.c 
int				rgb(int red, int green, int blue);
unsigned int	ft_hsl(unsigned int i);
int				color_z(t_point pt0, t_point pt1, t_map map, float dist);

//math_utils.c
float			ft_dist(float x0, float x1, float y0, float y1);
float			x_proj(t_map map, int x, int y);
float			y_proj(t_map map, int x, int y, int z);
int				min(int a, int b);
int				ft_abs(int a);

//free.c
void			free_tab(int **tab, int size);
void			free_doublechar(char **str);
void			free_env(t_env *fdf);
void			quit(int a, int **tab, int x_size);

// mlx.c
int				key_hook(int keycode, t_env *param);
int				create_env(t_env *fdf, char *str);
void			ft_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif
