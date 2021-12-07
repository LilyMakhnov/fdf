#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

typedef struct s_point
{
	int x;
	int y;
}	t_point;

typedef struct s_map
{
	int x_size;
	int y_size;
	int scale;
	int offset_x;
	int offset_y;
	t_point pt1;
	t_point pt2;
}	t_map;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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

int x_proj(t_map map, int x, int y)
{
	float ret;

	ret = 1.4142/2 * ((float)x - (float)y);
	return (map.scale * ret);
}

int y_proj(t_map map, int x, int y, int z)
{
	float ret;

	ret = -1.4142/1.7321 * (float)z + 1/2.4495 * ((float)x + (float)y);
	return (map.scale * ret);
}

t_point	set_point(t_map map, int **tab, int i, int j)
{
	t_point pnt;

	pnt.x = map.offset_x + x_proj(map, i, j);
	pnt.y = map.offset_y + y_proj(map, i, j, tab[i][j]); 
	return (pnt);
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
			draw_line(img, map.pt1, map.pt2);
			if (j + 1 < map.y_size)
			{
				map.pt2 = set_point(map, tab, i, j + 1);
				draw_line(img, map.pt1, map.pt2);
			}
		}
		if (j + 1 < map.y_size)
		{
			map.pt1 = set_point(map, tab, i, j);
			map.pt2 = set_point(map, tab, i, j + 1);
			draw_line(img, map.pt1, map.pt2);	
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

	parse_line = ft_split(*line, ' ');
	if (!parse_line)
		quit(1, 0, 0);
	free(*line);
	*line = NULL;
	while (parse_line[map->x_size] && !(map->y_size))
		(map->x_size)++;
	free_doublechar(parse_line);
	parse_line = NULL;
	(map->y_size)++;
	return (get_next_line(fd, line));
}


void check_map(t_map *map, char **argv)
{
	int fd;
	int gnl;
	char *line;

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

int main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	int	**tab;
	t_map map;

	if (argc != 2)
		return (0);
	check_map(&map, argv);
	map.offset_x = 500;
	map.offset_y = 500;
	map.scale = 20;
	tab = alloc_tab(map.x_size, map.y_size);
	fill_tab(tab, map, argv);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "FdF");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
//	my_mlx_pixel_put(&img, 5, 5, 0x00FFFF00);
	draw_map(tab, map, &img);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	free_tab(tab, map);
	


	return (0);
}
