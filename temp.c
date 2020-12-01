#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#include "key_macos.h"
#include <mlx.h>
#define PI 3.1415926535
#define P2 PI / 2
#define P3 3 * PI / 2
#define DR 0.0174533

# define MAPX 8
# define MAPY 8
# define MAPS 64
# define BLOCK 64

# define WIDTH 1024
# define TO_COORD(X, Y) ((int)floor(Y) * WIDTH + (int)floor(X))
typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;
typedef struct	s_player
{
	double		px;
	double		py;
	double		pdx;
	double		pdy;
	double		pa;
}				t_player;
typedef struct	s_window
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_player	player;
	int			width;
	int			height;
	int			map_color;
	int			wall_color;
	int			grid_color;
	int			row_count;
	int			column_count;
}				t_window;
int				map[MAPY][MAPX] =
{
	{1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,1},
	{1,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1}
};
void	img_clear(t_window *window)
{
	int		i;
	int		j;
	i = 0;
	while (i < window->height)
	{
		j = 0;
		while (j < window->width)
		{
			window->img.data[i * window->width + j] = 0x000000;
			j++;
		}
		i++;
	}
}
void	draw_line(t_window *window, double x1, double y1, double x2, double y2, int color)
{
	double	deltaX;
	double	deltaY;
	double	step;
	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	if (step != 0)
	{
		deltaX /= step;
		deltaY /= step;
		while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
		{
			window->img.data[TO_COORD(x1, y1)] = color;
			x1 += deltaX;
			y1 += deltaY;
		}
	}
}
void			move_dot_left(t_window *window)
{
	window->player.pa -= 0.1;
	if (window->player.pa < 0)
	{
		window->player.pa += 2 * PI;
	}
	window->player.pdx = cos(window->player.pa) * 5;
	window->player.pdy = sin(window->player.pa) * 5;
}
void			move_dot_down(t_window *window)
{
	int			old_x;
	int			old_y;
	int			count_w;
	int			count_h;
	int			px;
	int			py;
	int			flag;
	
	px = (int)window->player.px;
	py = (int)window->player.py;
	old_x = (int)window->player.px;
	old_y = (int)window->player.py;
	if ((0 < old_x - 2 && old_x + 2 < window->width / 2) && (0 < old_y - 2 && old_y + 2 < window->height))
	{
		count_h = old_y - 2;
		while (count_h <= old_y + 2)
		{
			count_w = old_x - 2;
			while (count_w <= old_x + 2)
			{
				window->img.data[count_h * window->width + count_w] = window->map_color;
				count_w++;
			}
			count_h++;
		}
		if (map[(int)(old_y - window->player.pdy) / BLOCK][(int)(old_x - window->player.pdx) / BLOCK] == 0)
		{
			window->player.px -= (int)window->player.pdx;
			window->player.py -= (int)window->player.pdy;
		}
		count_h = (int)window->player.py - 2;
		while (count_h <= (int)window->player.py + 2)
		{
			count_w = (int)window->player.px - 2;
			while (count_w <= (int)window->player.px + 2)
			{
				window->img.data[count_h * window->width + count_w] = 0xFF0000;
				count_w++;
			}
			count_h++;
		}
	}
}
void			move_dot_right(t_window *window)
{
	window->player.pa += 0.1;
	if (window->player.pa > 2 * PI)
	{
		window->player.pa -= 2 * PI;
	}
	window->player.pdx = cos(window->player.pa) * 5;
	window->player.pdy = sin(window->player.pa) * 5;
}
void			move_dot_up(t_window *window)
{
	int			old_x;
	int			old_y;
	int			count_w;
	int			count_h;
	int			px;
	int			py;
	int			flag;
	
	px = (int)window->player.px;
	py = (int)window->player.py;
	old_x = (int)window->player.px;
	old_y = (int)window->player.py;
	if ((0 < old_x - 2 && old_x + 2 < window->width / 2) && (0 < old_y - 2 && old_y + 2 < window->height))
	{
		count_h = old_y - 2;
		while (count_h <= old_y + 2)
		{
			count_w = old_x - 2;
			while (count_w <= old_x + 2)
			{
				window->img.data[count_h * window->width + count_w] = window->map_color;
				count_w++;
			}
			count_h++;
		}
		if (map[(int)(old_y + window->player.pdy) / BLOCK][(int)(old_x + window->player.pdx) / BLOCK] == 0)
		{
			window->player.px += (int)window->player.pdx;
			window->player.py += (int)window->player.pdy;
		}
		count_h = (int)window->player.py - 2;
		while (count_h <= (int)window->player.py + 2)
		{
			count_w = (int)window->player.px - 2;
			while (count_w <= (int)window->player.px + 2)
			{
				window->img.data[count_h * window->width + count_w] = 0xFF0000;
				count_w++;
			}
			count_h++;
		}
	}
}
void			drawMap2D(t_window *window)
{
	int			i;
	int			j;
	int			k;
	int			l;
	i = 0;
	while (i < MAPY)
	{
		j = 0;
		while (j < MAPX)
		{
			if (map[i][j] == 1)
			{
				k = i * BLOCK;
				while (k < i * BLOCK + BLOCK)
				{
					l = j * BLOCK;
					while (l < j * BLOCK + BLOCK)
					{
						window->img.data[k * window->width + l] = window->wall_color;
						l++;
					}
					k++;
				}
			}
			j++;
		}
		i++;
	}
}
void			drawGrid(t_window *window)
{
	int			draw_position;
	int			index;

	index = 1;
	while (index < window->row_count)
	{
		draw_position = 0;
		while (draw_position <= window->width / 2)
		{
			window->img.data[index * (window->width * window->height / window->row_count) + draw_position] = window->grid_color;
			draw_position++;
		}
		index++;
	}
	index = 1;
	while (index < window->column_count)
	{
		draw_position = 0;
		while (draw_position <= window->height)
		{
			window->img.data[index * (window->width / 2 / window->column_count) + draw_position * (window->width)] = window->grid_color;
			draw_position++;
		}
		index++;
	}
}
double			dist(double ax, double ay, double bx, double by, double ang)
{
	return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}
void			drawRays3D(t_window *window)
{
	int			i;
	int			r, mx, my, mp, dof;
	double		rx, ry, ra, xo, yo;
	double		disH, disV, hx, hy, vx, vy;
	double		disT, lineH, lineO;
	double		ca;
	ra = window->player.pa - DR * 30;
	if (ra < 0)
	{
		ra += 2 * PI;
	}
	if (ra > 2 * PI)
	{
		ra -= 2 * PI;
	}
	r = 0;
	while (r < 60)
	{
		dof = 0;
		double aTan = -1/tan(ra);
		disH = 1000000;
		hx = window->player.px;
		hy = window->player.py;
		if (ra > PI)	// looking up
		{
			ry = (((int)window->player.py >> 6) << 6) - 0.0001;
			rx = (window->player.py - ry) * aTan + window->player.px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)	// looking down
		{
			ry = (((int)window->player.py >> 6) << 6) + 64;
			rx = (window->player.py - ry) * aTan + window->player.px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)	// looking straight left or right
		{
			rx = window->player.px;
			ry = window->player.py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * MAPX + mx;
			if (mp > 0 && mp < MAPX * MAPY && map[my][mx] > 0) // hit wall
			{
				hx = rx;
				hy = ry;
				disH = dist(window->player.px, window->player.py, hx, hy, ra);
				dof = 8;
			}
			else	// next line
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		dof = 0;
		double nTan = -tan(ra);
		disV = 1000000;
		vx = window->player.px;
		vy = window->player.py;
		if (ra > P2 && ra < P3)	// looking left
		{
			rx = (((int)window->player.px >> 6) << 6) - 0.0001;
			ry = (window->player.px - rx) * nTan + window->player.py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3)	// looking right
		{
			rx = (((int)window->player.px >> 6) << 6) + 64;
			ry = (window->player.px - rx) * nTan + window->player.py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)	// looking straight up or down
		{
			rx = window->player.px;
			ry = window->player.py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * MAPX + mx;
			if (mp > 0 && mp < MAPX * MAPY && map[my][mx] > 0) // hit wall
			{
				vx = rx;
				vy = ry;
				disV = dist(window->player.px, window->player.py, vx, vy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		int color;
		if (disV < disH)
		{
			rx = vx;
			ry = vy;
			disT = disV;
			color = 0xAA0000;
		}
		if (disV > disH)
		{
			rx = hx;
			ry = hy;
			disT = disH;
			color = 0xFF0000;
		}
		draw_line(window, (int)window->player.px, (int)window->player.py, (int)rx, (int)ry, 0x00FF00);
		ca = window->player.pa - ra;
		if (ca < 0)
		{
			ca += 2 * PI;
		}
		if (ca > 2 * PI)
		{
			ca -= 2 * PI;
		}
		disT = disT * cos(ca);
		lineH = (MAPS * 320) / disT;
		lineO = 160 - lineH / 2;
		if (lineH > 320)	// line height
		{
			lineH = 320;
		}
		if (lineO < 0)
		{
			lineO = 0;
		}
		for (int k = 0; k < 8; k++)
		{
			draw_line(window, (int)(r * 8 + 530 + k), 0, (int)(r * 8 + 530 + k), (int)lineO, 0x3b3b3b);
			draw_line(window, (int)(r * 8 + 530 + k), (int)lineO, (int)(r * 8 + 530 + k), (int)(lineO + lineH), color);
			draw_line(window, (int)(r * 8 + 530 + k), (int)(lineO + lineH), (int)(r * 8 + 530 + k), (int)(window->height), 0xFFFFFF);
		}
		ra += DR;
		if (ra < 0)
		{
			ra += 2 * PI;
		}
		if (ra > 2 * PI)
		{
			ra -= 2 * PI;
		}
		r++;
	}
}
void			init_player(t_window *window)
{
	int			count_w;
	int			count_h;
	img_clear(window);
	count_h = -1;
	while (++count_h < 512)
	{
		count_w = -1;
		while (++count_w < 512)
		{
			window->img.data[count_h * window->width + count_w] = window->map_color;
		}
	}
	count_h = (int)window->player.py - 2;
	while (count_h <= (int)window->player.py + 2)
	{
		count_w = (int)window->player.px - 2;
		while (count_w <= (int)window->player.px + 2)
		{
			window->img.data[count_h * window->width + count_w] = 0xFF0000;
			count_w++;
		}
		count_h++;
	}
	drawMap2D(window);
	drawGrid(window);
	drawRays3D(window);
	mlx_put_image_to_window(window->mlx, window->win, window->img.img_ptr, 0, 0);
}
int				press_key_for_dot(int key, t_window *window)
{
	if (key == KEY_A)
		move_dot_left(window);
	else if (key == KEY_S)
		move_dot_down(window);
	else if (key == KEY_D)
		move_dot_right(window);
	else if (key == KEY_W)
		move_dot_up(window);
	init_player(window);
	mlx_put_image_to_window(window->mlx, window->win, window->img.img_ptr, 0, 0);
	return (0);
}
int				main(void)
{
	t_window	window;
	window.width = 1024;
	window.height = 512;
	window.map_color = 0x808080;
	window.wall_color = 0xFFFFFF;
	window.grid_color = 0x000000;
	window.player.px = 300;
	window.player.py = 300;
	window.player.pdx = cos(window.player.pa) * 5;
	window.player.pdy = sin(window.player.pa) * 5;
	window.row_count = 8;
	window.column_count = 8;
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, window.width, window.height, "cat");
	window.img.img_ptr = mlx_new_image(window.mlx, window.width, window.height);
	window.img.data = (int *)mlx_get_data_addr(window.img.img_ptr, &window.img.bpp, &window.img.size_l, &window.img.endian);
	init_player(&window);
	mlx_hook(window.win, 2, 1, press_key_for_dot, &window);
	mlx_loop(window.mlx);
	return (0);
}