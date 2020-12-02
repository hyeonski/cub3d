/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:30:42 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/02 15:47:35 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ROWS 10
#define COLS 10
#define TILESIZE 50
#define MAPWIDTH TILESIZE * COLS
#define	MAPHEIGHT TILESIZE * ROWS
#define PI 3.1415926535
#define P2 PI / 2
#define P3 3 * PI / 2
#define DR 0.0174533
#define TO_COORD(X, Y) ((int)floor(Y) * MAPWIDTH + (int)floor(X))

#include "mlx.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "key_macos.h"
#include "cub3d.h"
#include <math.h>

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

void	init_player(t_game *game)
{
	game->player.px = (COLS / 2) * TILESIZE;
	game->player.py = (ROWS / 2) * TILESIZE;
	game->player.pa = P3;
	game->player.pdx = cos(game->player.pa) * 5;
	game->player.pdy = sin(game->player.pa) * 5;
	game->player.color = 0xFF0000;
	game->player.width = 5;
	game->player.height = 5;
	game->player.imgptr = mlx_new_image(game->mlx, game->player.width, game->player.height);
	game->player.data = (int *)mlx_get_data_addr(game->player.imgptr, &game->player.bpp, &game->player.size_l, &game->player.endian);
	draw_player(game);
}

void	map_init(t_game *game)
{
	int map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 1, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	memcpy(game->map, map, sizeof(int) * ROWS * COLS);
	game->tile.grid_color = 0xb3b3b3;
	game->tile.imgptr = mlx_new_image(game->mlx, MAPWIDTH, MAPHEIGHT);
	game->tile.data = (int *)mlx_get_data_addr(game->tile.imgptr, &game->tile.bpp, &game->tile.size_l, &game->tile.endian);
}

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, MAPWIDTH, MAPHEIGHT, "cub3d");
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
		game->player.px += (int)game->player.pdx;
		game->player.py += (int)game->player.pdy;
	}
	if (key == KEY_S)
	{
		game->player.px -= (int)game->player.pdx;
		game->player.py -= (int)game->player.pdy;
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
	return (0);
}

int		main_loop(t_game *game)
{
	draw_rectangles(game);
	mlx_put_image_to_window(game->mlx, game->win, game->tile.imgptr, 0, 0);
	draw_player(game);
	return (0);
}

int main(void)
{
	t_game game;
	
	window_init(&game);
	map_init(&game);
	init_player(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, key_input, &game);
	mlx_loop_hook(game.mlx, main_loop, &game);
	mlx_loop(game.mlx);
}
