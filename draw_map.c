/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 10:30:42 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/01 16:10:35 by hyeonski         ###   ########.fr       */
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
	mlx_put_image_to_window(game->mlx, game->win, game->player.imgptr, game->player.x, game->player.y);
}

void	init_player(t_game *game)
{
	game->player.x = (COLS / 2) * TILESIZE;
	game->player.y = (ROWS / 2) * TILESIZE;
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
		game->player.x -= 5;
	if (key == KEY_D)
		game->player.x += 5;
	if (key == KEY_W)
		game->player.y -= 5;
	if (key == KEY_S)
		game->player.y += 5;
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
