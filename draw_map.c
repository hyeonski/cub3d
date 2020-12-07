/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:30:42 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/07 14:56:06 by hyeonski         ###   ########.fr       */
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

void	drawMap2D(t_game *game)
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

void	drawGrid(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->map.imgptr, 0, 0);
}

void	drawRays3D(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win, game->map.imgptr, 0, 0);
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