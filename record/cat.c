/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:30:42 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/08 18:26:03 by hyeonski         ###   ########.fr       */
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

void		init_game(t_game *game)
{
	game->width = 1024;
	game->height = 512;
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, game->width, game->height, "cub3d");
}

void		init_map(t_game *game)
{
	int		map[MAPY][MAPX] =
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
	int w;
	int h;
	
	memcpy(game->map.map, map, sizeof(int) * MAPX * MAPY);
	game->map_color = 0x808080;
	game->wall_color = 0xFFFFFF;
	game->grid_color = 0x000000;
	game->row_count = 8;
	game->column_count = 8;
	game->map.imgptr = mlx_new_image(game->mlx, game->width, game->height);
	game->map.data = (int *)mlx_get_data_addr(game->map.imgptr, &game->map.bpp, &game->map.size_l, &game->map.endian);
	h = 0;
	while (h < 512)
	{
		w = 0;
		while (w < 512)
		{
			game->map.data[h * game->width + w] = game->map_color;
			w++;
		}
		h++;
	}
}

void	draw_rectangle(t_game *game, int x, int y)
{
	int i;
	int j;

	x *= BLOCK;
	y *= BLOCK;
	i = 0;
	while (i < BLOCK)
	{
		j = 0;
		while (j < BLOCK)
		{
			game->map.data[(y + i) * game->width + x + j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}

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
			game->map.data[TO_COORD(x1, y1)] = color;
			x1 += deltaX;
			y1 += deltaY;
		}
	}
}

void	drawMap2D(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < MAPY)
	{
		j = 0;
		while (j < MAPX)
		{
			if (game->map.map[i][j] == 1)
				draw_rectangle(game, j, i);
			j++;
		}
		i++;
	}
}

void	drawGrid(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < MAPX)
	{
		draw_line(game, i * BLOCK, 0, i * BLOCK, game->height, game->grid_color);
		i++;
	}
	draw_line(game, MAPX * BLOCK - 1, 0, MAPX * BLOCK - 1, game->height, game->grid_color);
	j = 0;
	while (j < MAPY)
	{
		draw_line(game, 0, j * BLOCK, WIDTH / 2, j * BLOCK, game->grid_color);
		j++;
	}
	draw_line(game, 0, MAPY * BLOCK - 1, WIDTH / 2, MAPY * BLOCK - 1, game->grid_color);
}

double			dist(double ax, double ay, double bx, double by, double ang)
{
	return ( sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	drawRays3D(t_game *game)
{
	int			r, mx, my, mp, dof;
	double		rx, ry, ra, xo, yo;
	double		disH, disV, hx, hy, vx, vy;
	double		disT, lineH, lineO;
	double		ca;
	int			color;

	ra = game->player.pa - DR * 30;
	r = 0;
	if (ra < 0)
	{
		ra += 2 * PI;
	}
	if (ra > 2 * PI)
	{
		ra -= 2 * PI;
	}
	while (r < 60)
	{
		//--Check Horizontal line--
		dof = 0;
		double aTan = -1 / tan(ra);
		disH = 1000000;
		hx = game->player.px;
		hy = game->player.py;
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
			mp = my * MAPX + mx;
			if (mp > 0 && mp < MAPX * MAPY && game->map.map[my][mx] > 0) // hit wall
			{
				hx = rx;
				hy = ry;
				disH = dist(game->player.px, game->player.py, hx, hy, ra);
				dof = 8;
			}
			else	// next line
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		//--Check Vertical line--
		dof = 0;
		double nTan = -tan(ra);
		disV = 1000000;
		vx = game->player.px;
		vy = game->player.py;
		if (ra > P2 && ra < P3)	// looking left
		{
			rx = (((int)game->player.px >> 6) << 6) - 0.0001;
			ry = (game->player.px - rx) * nTan + game->player.py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3)	// looking right
		{
			rx = (((int)game->player.px >> 6) << 6) + 64;
			ry = (game->player.px - rx) * nTan + game->player.py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI)	// looking straight up or down
		{
			rx = game->player.px;
			ry = game->player.py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) >> 6;
			my = (int)(ry) >> 6;
			mp = my * MAPX + mx;
			if (mp > 0 && mp < MAPX * MAPY && game->map.map[my][mx] > 0) // hit wall
			{
				vx = rx;
				vy = ry;
				disV = dist(game->player.px, game->player.py, vx, vy, ra);
				dof = 8;
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
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
		draw_line(game, (int)game->player.px, (int)game->player.py, (int)rx, (int)ry, 0x00FF00);
		
		//--Draw 3D Walls--
		ca = game->player.pa - ra;
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
		if (lineH > 320)
		{
			lineH = 320;
		}
		lineO = 160 - lineH / 2;
		for (int k = 0; k < 8; k++)
		{
			draw_line(game, (int)(r * 8 + 530 + k), 0, (int)(r * 8 + 530 + k), (int)lineO, 0x3b3b3b);
			draw_line(game, (int)(r * 8 + 530 + k), (int)lineO, (int)(r * 8 + 530 + k), (int)(lineO + lineH), color);
			draw_line(game, (int)(r * 8 + 530 + k), (int)(lineO + lineH), (int)(r * 8 + 530 + k), (int)(game->height), 0xFFFFFF);
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

void		init_player(t_game *game)
{
	int		w;
	int		h;
	
	game->player.color = 0xFF0000;
	game->player.px = 300;
	game->player.py = 300;
	game->player.pa = P3;
	game->player.pdx = cos(game->player.pa) * 5;
	game->player.pdy = sin(game->player.pa) * 5;
	
	h = (int)game->player.py - 2;
	while (h <= (int)game->player.py + 2)
	{
		w = (int)game->player.px - 2;
		while (w <= (int)game->player.px + 2)
		{
			game->map.data[h * game->width + w] = 0xFF0000;
			w++;
		}
		h++;
	}
	drawMap2D(game);
	drawGrid(game);
	drawRays3D(game);
	mlx_put_image_to_window(game->mlx, game->win, game->map.imgptr, 0, 0);
}


// void test(t_game *game)
// {
// 	int w;
// 	int h;

// 	h = 0;
// 	while (h < game->height)
// 	{
// 		w = 512;
// 		while (w < game->width)
// 		{
// 			game->map.data[h * game->width + w] = 0xffffff;
// 			w++;
// 		}
// 		h++;
// 	}
// }

void		map_reinit(t_game *game)
{
	int		w;
	int		h;
	
	h = 0;
	while (h < game->height)
	{
		w = 0;
		while (w < game->width)
		{
			game->map.data[h * game->width + w] = 0x000000;
			w++;
		}
		h++;
	}
	h = 0;
	while (h < 512)
	{
		w = 0;
		while (w < 512)
		{
			game->map.data[h * game->width + w] = game->map_color;
			w++;
		}
		h++;
	}
	h = (int)game->player.py - 2;
	while (h <= (int)game->player.py + 2)
	{
		w = (int)game->player.px - 2;
		while (w <= (int)game->player.px + 2)
		{
			game->map.data[h * game->width + w] = 0xFF0000;
			w++;
		}
		h++;
	}
	drawMap2D(game);
	drawGrid(game);
	drawRays3D(game);
}

void	player_move_left(t_game *game)
{
	game->player.pa -= 0.1;
	if (game->player.pa < 0)
		game->player.pa += 2 * PI;
	game->player.pdx = cos(game->player.pa) * 5;
	game->player.pdy = sin(game->player.pa) * 5;
}

void	player_move_down(t_game *game)
{
	int			old_x;
	int			old_y;
	int			w;
	int			h;
	
	old_x = (int)game->player.px;
	old_y = (int)game->player.py;
	if ((0 < old_x - 2 && old_x + 2 < game->width / 2) && (0 < old_y - 2 && old_y + 2 < game->height))
	{
		h = old_y - 2;
		while (h <= old_y + 2)
		{
			w = old_x - 2;
			while (w <= old_x + 2)
			{
				game->map.data[h * game->width + w] = game->map_color;
				w++;
			}
			h++;
		}
		if (game->map.map[(int)(old_y - game->player.pdy) / BLOCK][(int)(old_x - game->player.pdx) / BLOCK] == 0)
		{
			game->player.px -= (int)game->player.pdx;
			game->player.py -= (int)game->player.pdy;
		}
		h = (int)game->player.py - 2;
		while (h <= (int)game->player.py + 2)
		{
			w = (int)game->player.px - 2;
			while (w <= (int)game->player.px + 2)
			{
				game->map.data[h * game->width + w] = 0xFF0000;
				w++;
			}
			h++;
		}
	}
}

void	player_move_right(t_game *game)
{
	game->player.pa += 0.1;
	if (game->player.pa > 2 * PI)
		game->player.pa -= 2 * PI;
	game->player.pdx = cos(game->player.pa) * 5;
	game->player.pdy = sin(game->player.pa) * 5;
}

void	player_move_up(t_game *game)
{
	int			old_x;
	int			old_y;
	int			w;
	int			h;
	
	old_x = (int)game->player.px;
	old_y = (int)game->player.py;
	if ((0 < old_x - 2 && old_x + 2 < game->width / 2) && (0 < old_y - 2 && old_y + 2 < game->height))
	{
		h = old_y - 2;
		while (h <= old_y + 2)
		{
			w = old_x - 2;
			while (w <= old_x + 2)
			{
				game->map.data[h * game->width + w] = game->map_color;
				w++;
			}
			h++;
		}
		if (game->map.map[(int)(old_y + game->player.pdy) / BLOCK][(int)(old_x + game->player.pdx) / BLOCK] == 0)
		{
			game->player.px += (int)game->player.pdx;
			game->player.py += (int)game->player.pdy;
		}
		h = (int)game->player.py - 2;
		while (h <= (int)game->player.py + 2)
		{
			w = (int)game->player.px - 2;
			while (w <= (int)game->player.px + 2)
			{
				game->map.data[h * game->width + w] = 0xFF0000;
				w++;
			}
			h++;
		}
	}
}

int			key_input(int key, t_game *game)
{
	if (key == KEY_A)
	{
		player_move_left(game);
	}
	if (key == KEY_S)
	{
		player_move_down(game);
	}
	if (key == KEY_D)
	{
		player_move_right(game);
	}
	if (key == KEY_W)
	{
		player_move_up(game);
	}
	if (key == KEY_ESC)
	{
		exit(0);
	}
	map_reinit(game);
	mlx_put_image_to_window(game->mlx, game->win, game->map.imgptr, 0, 0);
	return (0);
}

int			main(void)
{
	t_game	game;

	init_game(&game);
	init_map(&game);
	init_player(&game);
	mlx_hook(game.win, 2, 1, key_input, &game);
	mlx_loop(game.mlx);
	return (0);
}