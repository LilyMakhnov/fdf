#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_env
{
	void *mlx;
	void *win;
	t_data img;
}	t_env;

typedef struct s_offset
{
	int x_min;
	int y_min;
	int x_max;
	int y_max;
}	t_offset;

typedef struct s_point
{
	float x;
	float y;
	int x3d;
	int y3d;
	int z3d;
}	t_point;

typedef struct s_map
{
	int x_size;
	int y_size;
	int scale;
	int offset_x;
	int offset_y;
	t_offset offset;
	t_point pt1;
	t_point pt2;
}	t_map;


int max(int a, int b)
{
	if (a > b)
		return (a);
	else 
		return (b);
}

int min(int a, int b)
{
	if (a < b)
		return (a);
	else 
		return (b);
}

void	quit(int a, int **tab, int x_size)
{
	if (tab)
	{
		while (x_size--)
			free(tab[x_size]);
		free(tab);
	}
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
	*(unsigned int*)dst = color;
}

void	plotLineLow(t_data *data, t_point pt0, t_point pt1)
{
	int D;
	int x;
	int y;

 	D = 2 * abs((int)pt1.y - (int)pt0.y) - (pt1.x - pt0.x);
    y = pt0.y;
	x = pt0.x;
	while (x < pt1.x)
	{
   		my_mlx_pixel_put(data, x, y, 0x00FFF000);
   	   	if (D > 0)
		{
			if (pt1.y > pt0.y)
   	      	 	y++;
			else
				y--;
   	       	D = D + (2 * (abs((int)pt1.y - (int)pt0.y) - (pt1.x - pt0.x)));
		}
   	   	else
   	       	D = D + 2 * abs((int)pt1.y - (int)pt0.y);
		x++;
	}
}

void	plotLineHigh(t_data *data, t_point pt0, t_point pt1)
{
	int D;
	int x;
	int y;

    D = 2 * abs((int)pt1.x - (int)pt0.x) - (pt1.y - pt0.y);
    x = pt0.x;
	y = pt0.y;
	while (y < pt1.y)
	{
        my_mlx_pixel_put(data, x, y, 0x00FFF000);
        if (D > 0)
		{
            if (pt1.x > pt0.x)
   	      	 	x++;
			else
				x--;
            D = D + (2 * (abs((int)pt1.x - (int)pt0.x) - (pt1.y - pt0.y)));
		}
        else
            D = D + 2*abs((int)pt1.x - (int)pt0.x);
		y++;
	}
}

void drawline(t_data *data, t_point pt0, t_point pt1)
{
    if (abs((int)pt1.y - (int)pt0.y) < abs((int)pt1.x - (int)pt0.x))
        if (pt0.x > pt1.x)
            plotLineLow(data, pt1, pt0);
        else
            plotLineLow(data, pt0, pt1);
    else
        if (pt0.y > pt1.y)
            plotLineHigh(data, pt1, pt0);
        else
            plotLineHigh(data, pt0, pt1);
}

void	draw_line(t_data *data, t_point pt1, t_point pt2)
{
	float a;
	float b;
	int x;
	int y;

	if (pt1.x != pt2.x)
	{
		a = (float)(pt2.y - pt1.y)/(pt2.x - pt1.x);
		b = (float)(pt2.x * pt1.y - pt1.x * pt2.y)/(pt2.x - pt1.x);
		x = min(pt1.x, pt2.x) - 1; 
		while (++x < max(pt1.x, pt2.x))
			my_mlx_pixel_put(data, x, (int)(x * a + b) , 0x00FFF000 );
		y = min(pt1.y, pt2.y) + 1; 
		while (++y < max(pt1.y, pt2.y))
			if (a != 0)
				my_mlx_pixel_put(data, (int)(y - b)/a, y , 0x00FFF000 );
	}
	else
	{
		y = min(pt1.y, pt2.y);
		while (y < max(pt1.y, pt2.y))
			my_mlx_pixel_put(data, pt1.x, y++, 0x00FFF000 );
	}
}

void map_init(t_map *map)
{
	map->x_size = 0;
	map->y_size = 0;
}

float x_proj(t_map map, int x, int y)
{
	float ret;

	ret = 1.4142/2 * ((float)x - (float)y);
	return (map.scale * ret);
}

float y_proj(t_map map, int x, int y, int z)
{
	float ret;

	ret = 1.4142/1.7321 * (float)y + 1/2.4495 * ((float)x - (float)z);
	return (map.scale * ret);
}

t_point	set_point(t_map map, int **tab, int i, int j)
{
	t_point pnt;

	pnt.x = map.offset_x + x_proj(map, i, j);
	pnt.y = map.offset_y + y_proj(map, i, j, tab[i][j]); 
	pnt.x3d = i;
	pnt.y3d = j;
	pnt.z3d = tab[i][j];
	return (pnt);
}

t_offset	shift_offset(int **tab, t_map map)
{
	t_offset offset;
	int i;

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
	int i;
	int j;

	j = -1;
	while (++j < map.y_size)
	{
		i = -1;
		while(++i + 1 < map.x_size)
		{
			map.pt1 = set_point(map, tab, i, j);
			map.pt2 = set_point(map, tab, i + 1, j);
			drawline(img, map.pt1, map.pt2);
			if (j + 1 < map.y_size)
			{
				map.pt2 = set_point(map, tab, i, j + 1);
				drawline(img, map.pt1, map.pt2);
			}
		}
		if (j + 1 < map.y_size)
		{
			map.pt1 = set_point(map, tab, i, j);
			map.pt2 = set_point(map, tab, i, j + 1);
			drawline(img, map.pt1, map.pt2);	
		}
	}
}

void free_tab(int **tab, t_map map)
{
	int i;

	i = 0;
	while (i < map.x_size)
		free(tab[i++]);
	free(tab);
}

void	free_doublechar(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int check_line(int fd, char **line, t_map *map)
{
	char **parse_line;
	int i;

	parse_line = ft_split(*line, ' ');
	if (!parse_line)
		quit(1, 0, 0);
	free(*line);
	*line = NULL;
	i = 0;
	while (parse_line[i])
		i++;
	free_doublechar(parse_line);
	parse_line = NULL;
	if (!map->x_size)
			map->x_size = i;
	else if (map->x_size != i)
			quit(1, 0, 0);
	(map->y_size)++;
	return (get_next_line(fd, line));
}


void check_map(t_map *map, char **argv)
{
	int fd;
	int gnl;
	char *line;

	map->x_size = 0;
	map->y_size = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		quit(1, 0, 0);
	map_init(map);
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
	int **tab;
	int i;

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
		char **parse_line;
		static int j = 0;
		int i;

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
	int fd;
	int gnl;
	char *line;

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

int	key_hook(int keycode,t_env *param)
{
	(void)param;
	(void)keycode;
	//ft_putnbr_fd(keycode, 1);
	if (keycode == 65307)
	{
		mlx_destroy_image (param->mlx, param->img.img);
		mlx_destroy_window (param->mlx, param->win);
		free(param->mlx);
		exit(0);
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_env fdf;
//	void	*mlx;
//	void	*mlx_win;
//	t_data	img;
	int	**tab;
	t_map map;
	t_offset off;

	if (argc != 2)
		return (0);
	check_map(&map, argv);
	map.offset_x = 1920 / 2;
	map.offset_y = 1080 / 2;
	map.scale = 1;
	tab = alloc_tab(map.x_size, map.y_size);
	fill_tab(tab, map, argv);
	fdf.mlx = mlx_init();
	if (!fdf.mlx)
		return (0);
	fdf.win = mlx_new_window(fdf.mlx, 1920, 1080, "FdF");
	if (!fdf.win)
		return (0);
	fdf.img.img = mlx_new_image(fdf.mlx, 1920, 1080);
	fdf.img.addr = mlx_get_data_addr(fdf.img.img, &fdf.img.bits_per_pixel, &fdf.img.line_length,
								&fdf.img.endian);
//	my_mlx_pixel_put(&img, 5, 5, 0x00FFFF00);
	off = shift_offset(tab, map);
	map.scale = min(1920 / (off.x_max-off.x_min), 1080 / (off.y_max-off.y_min)) * 0.8;
	if (map.scale < 1)
		map.scale = 1;
	off = shift_offset(tab, map);
	map.offset_x = 2 * map.offset_x - (off.x_max + off.x_min)/2;
	map.offset_y = 2 * map.offset_y - (off.y_max + off.y_min)/2;
	off = shift_offset(tab, map);
	draw_map(tab, map, &fdf.img);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img.img, 0, 0);
	free_tab(tab, map);

	mlx_key_hook (fdf.win, &key_hook, &fdf);
//	mlx_hook(mlx_win, 2, 0, &key_event_press, &e);
//	mlx_key_hook(mlx_win, &key_event_take_off, &e);
//	mlx_loop_hook(mlx, &alteration, &e);
	mlx_loop(fdf.mlx);

	free(fdf.mlx);
	return (0);
}
