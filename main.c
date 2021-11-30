#include "mlx_linux/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

/*
typedef struct s_point
{
	int x;
	int y;
	int z;
}	t_point;
*/
typedef struct s_map
{
	int x_size;
	int y_size;
}	t_map;
/*
typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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

	a = (float)(pt2.y - pt1.y)/(pt2.x - pt1.x);
	b = (float)(pt2.x * pt1.y - pt1.x * pt2.y)/(pt2.x - pt1.x);

	x = pt1.x; 
	printf("%f\n", x*a+b);
	while (x < pt2.x)
	{
		my_mlx_pixel_put(data, x, (int)(x * a + b) , 0x00FF0000 );
		x++;
	}
}

int	ft_strtab_len(char **str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
*/
void map_init(t_map *map)
{
	map->x_size = 0;
	map->y_size = 0;
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
}

void check_map(t_map *map, char **argv)
{
	int fd;
	int gnl;
	char *line;
	char **parse_line;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		quit(1, 0, 0);
	map_init(map);
	line = NULL;
	gnl = get_next_line(fd, &line);
	while(gnl > 0)
	{
		parse_line = ft_split(line, ' ');
		if (!parse_line)
			quit(1, 0, 0);
		free(line);
		line = NULL;
		while (parse_line[map->x_size] && !(map->y_size))
			(map->x_size)++;
		free(parse_line);
		parse_line = NULL;
		(map->y_size)++;
		gnl = get_next_line(fd, &line);
	}
	if (close(fd) || gnl < 0)
		quit(1, 0, 0);
}

int	**alloc_tab(int x_size, int y_size)
{
	int **tab;
	int i;

	tab = malloc(sizeof(int) * x_size);
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

void	fill_tab(int **tab, t_map map, char **argv)
{
	int fd;
	int gnl;
	char *line;
	char **parse_line;
	int i;
	int j;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		quit(1, 0, 0);
	line = NULL;
	gnl = get_next_line(fd, &line);
	j = 0;
	while (gnl > 0)
	{
		parse_line = ft_split(line, ' ');
		if (!parse_line)
			quit(1, tab, map.x_size);
		i = -1;
		while (parse_line[++i])
			tab[j][i] = atoi(parse_line[i]);
		free(parse_line);
		parse_line = NULL;
		gnl = get_next_line(fd, &line);
		j++;
	}
	free (line);
}

int main(int argc, char **argv)
{
	t_map map;
	int **tab;

	if (argc != 2)
		return (0);
	check_map(&map, argv);
	tab = alloc_tab(map.x_size, map.y_size);
	fill_tab(tab, map, argv);

	return (0);
}
/*
int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
	t_point pt1;
	t_point pt2;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	pt1.x = 200;
	pt1.y = 100;
	pt2.x = 300;
	pt2.y = 500;	
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	draw_line(&img, pt1, pt2);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}*/
