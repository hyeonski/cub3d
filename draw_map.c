/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:30:42 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/02 17:57:09 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#include "mlx.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "key_macos.h"
#include "cub3d.h"
#include <math.h>
/*
void	draw_line(t_game *game, double x1, double y1, double x2, double y2, int color)
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
			game->tile.data[TO_COORD(x1, y1)] = color;
			x1 += deltaX;
			y1 += deltaY;
		}
	}
}

double			dist(double ax, double ay, double bx, double by)
{
	return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void			draw_grid(t_game *game)
{
	int			draw_position;
	int			index;

	index = 1;
	while (index < ROWS)
	{
		draw_position = 0;
		while (draw_position <= MAPWIDTH)
		{
			game->tile.data[index * (MAPWIDTH * MAPHEIGHT / ROWS) + draw_position] = game->tile.grid_color;
			draw_position++;
		}
		index++;
	}
	index = 1;
	while (index < COLS)
	{
		draw_position = 0;
		while (draw_position <= MAPHEIGHT)
		{
			game->tile.data[index * (MAPWIDTH / COLS) + draw_position * (MAPWIDTH)] = game->tile.grid_color;
			draw_position++;
		}
		index++;
	}
}

void	draw_rectangle(t_game *game, int x, int y)
{
	int i;
	int j;

	x *= TILESIZE;
	y *= TILESIZE;
	i = 0;
	while (i < TILESIZE)
	{
		j = 0;
		while (j < TILESIZE)
		{
			game->tile.data[(y + i) * MAPWIDTH + x + j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (game->map[i][j] == 1)
				draw_rectangle(game, j, i);
			j++;
		}
		i++;
	}
	draw_grid(game);
}
void	draw_player(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->player.height)
	{
		j = 0;
		while (j < game->player.width)
		{
			game->player.data[i * game->player.width + j] = game->player.color;
			j++;
		}	
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->player.imgptr, game->player.px, game->player.py);
}


void	draw_rays(t_game *game)
{
	int			r, mx, my, mp, dof;
	double		rx, ry, ra, xo, yo;

	r = 0;
	while (r < 1)
	{
		double aTan = -1 / tan(ra);
		if (ra > PI)	// looking up
		{
			ry = (((int)game->player.py >> 6) << 6) - 0.0001;
			rx = (game->player.py - ry) * aTan + game->player.px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)	// looking down
		{
			ry = (((int)game->player.py >> 6) << 6) + 64;
			rx = (game->player.py - ry) * aTan + game->player.px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI)	// looking straight left or right
		{
			rx = game->player.px;
			ry = game->player.py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * COLS + mx;
			if (mp > 0 && mp < COLS * ROWS && game->map[my][mx] > 0) // hit wall
			{
				// hx = rx;
				// hy = ry;
				// disH = dist(game->player.px, window->player.py, hx, hy, ra);
				dof = 8;
			}
			else	// next line
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		draw_line(game, (int)game->player.px, (int)game->player.py, (int)rx, (int)ry, 0x00FF00);
	}
}

int		main_loop(t_game *game)
{
	draw_rectangles(game);
	draw_rays(game);
	mlx_put_image_to_window(game->mlx, game->win, game->tile.imgptr, 0, 0);
	draw_player(game);
	return (0);
}*/

void	img_clear(t_game *game)
{
	int		i;
	int		j;
	i = 0;
	while (i < game->height)
	{
		j = 0;
		while (j < game->width)
		{
			game->map.data[i * game->width + j] = 0x000000;
			j++;
		}
		i++;
	}
}

void	window_init(t_game *game)
{
	game->width = 1024;
	game->height = 512;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height, "cub3d");
}

void	map_init(t_game *game)
{
	int	map[MAPY][MAPX] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1}
	};

	memcpy(game->map.map, map, sizeof(int) * MAPX * MAPY);
	game->map.grid_color = 0xb3b3b3;
	game->map.wall_color = 0xFFFFFF;
	game->map.imgptr = mlx_new_image(game->mlx, game->width, game->height);
	game->map.data = (int *)mlx_get_data_addr(game->map.imgptr, &game->map.bpp, &game->map.size_l, &game->map.endian);
}

void	init_player(t_game *game)
{
	int			count_w;
	int			count_h;
	
	
	game->player.px = (double)game->width / 2;
	game->player.py = (double)game->height / 2;
	game->player.pa = P3;
	game->player.pdx = cos(game->player.pa) * 5;
	game->player.pdy = sin(game->player.pa) * 5;
	game->player.color = 0xFF0000;
	game->player.width = 5;
	game->player.height = 5;
	
	count_h = (int)game->player.py - 2;
	while (count_h <= (int)game->player.py + 2)
	{
		count_w = (int)game->player.px - 2;
		while (count_w <= (int)game->player.px + 2)
		{
			game->map.data[count_h * game->width + count_w] = 0xFF0000;
			count_w++;
		}
		count_h++;
	}
}

void			player_turn_left(t_game *game)
{
	game->player.pa -= 0.1;
	if (game->player.pa < 0)
		game->player.pa += 2 * PI;
	game->player.pdx = cos(game->player.pa) * 5;
	game->player.pdy = sin(game->player.pa) * 5;
}

void			player_turn_right(t_game *game)
{
	game->player.pa += 0.1;
	if (game->player.pa > 2 * PI)
		game->player.pa -= 2 * PI;
	game->player.pdx = cos(game->player.pa) * 5;
	game->player.pdy = sin(game->player.pa) * 5;
}

void			player_move_down(t_game *game)
{
	int			old_x;
	int			old_y;
	int			count_w;
	int			count_h;
	int			px;
	int			py;
	int			flag;
	
	px = (int)game->player.px;
	py = (int)game->player.py;
	old_x = (int)game->player.px;
	old_y = (int)game->player.py;
	if ((0 < old_x - 2 && old_x + 2 < game->width / 2) && (0 < old_y - 2 && old_y + 2 < game->height))
	{
		count_h = old_y - 2;
		while (count_h <= old_y + 2)
		{
			count_w = old_x - 2;
			while (count_w <= old_x + 2)
			{
				game->map.data[count_h * game->width + count_w] = 0x000000;
				count_w++;
			}
			count_h++;
		}
		if (game->map.map[(int)(old_y - game->player.pdy) / BLOCK][(int)(old_x - game->player.pdx) / BLOCK] == 0)
		{
			game->player.px -= (int)game->player.pdx;
			game->player.py -= (int)game->player.pdy;
		}
		count_h = (int)game->player.py - 2;
		while (count_h <= (int)game->player.py + 2)
		{
			count_w = (int)game->player.px - 2;
			while (count_w <= (int)game->player.px + 2)
			{
				game->map.data[count_h * game->width + count_w] = 0xFF0000;
				count_w++;
			}
			count_h++;
		}
	}
}

void			player_move_up(t_game *game)
{
	int			old_x;
	int			old_y;
	int			count_w;
	int			count_h;
	int			px;
	int			py;
	int			flag;
	
	px = (int)game->player.px;
	py = (int)game->player.py;
	old_x = (int)game->player.px;
	old_y = (int)game->player.py;
	if ((0 < old_x - 2 && old_x + 2 < game->width / 2) && (0 < old_y - 2 && old_y + 2 < game->height))
	{
		count_h = old_y - 2;
		while (count_h <= old_y + 2)
		{
			count_w = old_x - 2;
			while (count_w <= old_x + 2)
			{
				game->map.data[count_h * game->width + count_w] = 0x000000;
				count_w++;
			}
			count_h++;
		}
		if (game->map.map[(int)(old_y + game->player.pdy) / BLOCK][(int)(old_x + game->player.pdx) / BLOCK] == 0)
		{
			game->player.px += (int)game->player.pdx;
			game->player.py += (int)game->player.pdy;
		}
		count_h = (int)game->player.py - 2;
		while (count_h <= (int)game->player.py + 2)
		{
			count_w = (int)game->player.px - 2;
			while (count_w <= (int)game->player.px + 2)
			{
				game->map.data[count_h * game->width + count_w] = 0xFF0000;
				count_w++;
			}
			count_h++;
		}
	}
}

int		key_input(int key, t_game *game)
{
	if (key == KEY_A)
	{
		game->player.px += (int)(cos(game->player.pa - (PI / 2)) * 5);
		game->player.py += (int)(sin(game->player.pa - (PI / 2)) * 5);
	}
	if (key == KEY_D)
	{
		game->player.px += (int)(cos(game->player.pa + (PI / 2)) * 5);
		game->player.py += (int)(sin(game->player.pa + (PI / 2)) * 5);
	}
	if (key == KEY_W)
	{
		player_move_up(game);
	}
	if (key == KEY_S)
	{
		player_move_down(game);
	}
	if (key == KEY_AR_L)
	{
		game->player.pa -= 0.1;
		if (game->player.pa < 0)
			game->player.pa += 2 * PI;
		game->player.pdx = cos(game->player.pa) * 5;
		game->player.pdy = sin(game->player.pa) * 5;
	}
	if (key == KEY_AR_R)
	{
		game->player.pa += 0.1;
		if (game->player.pa > 2 * PI)
			game->player.pa -= 2 * PI;
		game->player.pdx = cos(game->player.pa) * 5;
		game->player.pdy = sin(game->player.pa) * 5;
	}
	if (key == KEY_ESC) 
		exit(0);
	mlx_put_image_to_window(game->mlx, game->win, game->map.imgptr, 0, 0);
	return (0);
}

int main(void)
{
	t_game game;
	
	window_init(&game);
	map_init(&game);
	img_clear(&game);
	init_player(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.map.imgptr, 0, 0);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, key_input, &game);
	//mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_loop(game.mlx);
}
