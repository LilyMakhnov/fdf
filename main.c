#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"
#include <math.h>

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
	int	x_min;
	int	y_min;
	int	x_max;
	int	y_max;
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
	int			scale;
	int			offset_x;
	int			offset_y;
	t_offset	offset;
	t_point		pt1;
	t_point		pt2;
}	t_map;

int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	quit(int a, int **tab, int x_size)
{
	if (tab)
		free_tab(tab, x_size);
	if (a == 1)
	{
		write (2, "ERROR\n", 6);
		exit(1);
	}
	else
		exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

float	ft_dist(float x0, float x1, float y0, float y1)
{
	return (sqrt(pow(x1 - x0, 2) + pow(y1 - y0, 2)));
}

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

void	plot_line_low(t_data *data, t_point pt0, t_point pt1,  t_map map)
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
		my_mlx_pixel_put(data, x, y, color_z(pt0, pt1, map, dist));
   	   	if (delta > 0)
		{
			if (pt1.y > pt0.y)
   	      	 	y++;
			else
				y--;
   	       	delta += (2 * (abs((int)pt1.y - (int)pt0.y) - (pt1.x - pt0.x)));
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
		my_mlx_pixel_put(data, x, y, color_z(pt0, pt1, map, dist));
        if (delta > 0)
		{
            if (pt1.x > pt0.x)
   	      	 	x++;
			else
				x--;
            delta += (2 * (abs((int)pt1.x - (int)pt0.x) - (pt1.y - pt0.y)));
		}
        else
            delta += 2*abs((int)pt1.x - (int)pt0.x);
		y++;
	}
}

void	drawline(t_data *data, t_point pt0, t_point pt1, t_map map)
{
    if (abs((int)pt1.y - (int)pt0.y) < abs((int)pt1.x - (int)pt0.x))
        if (pt0.x > pt1.x)
            plot_line_low(data, pt1, pt0, map);
        else
            plot_line_low(data, pt0, pt1, map);
    else
        if (pt0.y > pt1.y)
            plot_line_high(data, pt1, pt0, map);
        else
            plot_line_high(data, pt0, pt1, map);
}

float	x_proj(t_map map, int x, int y)
{
	float	ret;

	ret = 1.4142/2 * ((float)x - (float)y);
	return (map.scale * ret);
}

float	y_proj(t_map map, int x, int y, int z)
{
	float	ret;

	ret = 1.4142/1.7321 * (float)y + 1/2.4495 * ((float)x - (float)z);
	return (map.scale * ret);
}

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

void	draw_map(int **tab, t_map map, t_data *img)
{
	int	i;
	int	j;

	j = -1;
	while (++j < map.y_size)
	{
		i = -1;
		while(++i + 1 < map.x_size)
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

void	free_tab(int **tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
		free(tab[i++]);
	free(tab);
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
	while(gnl > 0)
		gnl = check_line(fd, &line, map);
	free(line);
	if (close(fd) || gnl < 0)
		quit(1, 0, 0);
}

int	**alloc_tab(int x_size, int y_size)
{
	int	**tab;
	int	i;

	tab = malloc(sizeof(int*) * x_size);
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

int	key_hook(int keycode, t_env *param)
{
	if (keycode == 65307)
	{
		mlx_destroy_image (param->mlx, param->img.img);
		mlx_destroy_window (param->mlx, param->win);
		free(param->mlx);
		exit(0);
	}
	return (0);
}

int	create_env(t_env *fdf, char *str)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (0);
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, str);
	if (!fdf->win)
		return (0);
	fdf->img.img = mlx_new_image(fdf->mlx, 1920, 1080);
	if (!fdf->img.img)
		return (0);
	fdf->img.addr = mlx_get_data_addr(fdf->img.img, &fdf->img.bits_per_pixel, &fdf->img.line_length,
								&fdf->img.endian);
	if (!fdf->img.addr)
		return (0);
	return (1);
}

void	ft_frame(int **tab, t_map *map)
{
	t_offset	off;

	map->offset_x = 1920 / 2;
	map->offset_y = 1080 / 2;
	map->scale = 1;
	off = shift_offset(tab, *map);
	map->scale = min(1920 / (off.x_max-off.x_min), 1080 / (off.y_max-off.y_min)) * 0.8;
	if (map->scale < 1)
		map->scale = 1;
	off = shift_offset(tab, *map);
	map->offset_x = 2 * map->offset_x - (off.x_max + off.x_min)/2;
	map->offset_y = 2 * map->offset_y - (off.y_max + off.y_min)/2;
}

void	free_env(t_env *fdf)
{
	if (fdf->mlx)
		{
			if (fdf->win)
				mlx_destroy_window (fdf->mlx, fdf->win);
			if (fdf->img.img)
				mlx_destroy_image (fdf->mlx, fdf->img.img);
			free(fdf->mlx);
		}
}

int	main(int argc, char **argv)
{
	t_env	fdf;
	int		**tab;
	t_map	map;

	if (argc != 2)
		return (0);
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
	mlx_key_hook (fdf.win, &key_hook, &fdf);
	mlx_loop(fdf.mlx);
	free_env(&fdf);
	return (0);
}
