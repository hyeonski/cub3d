/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:53:34 by hyeonski          #+#    #+#             */
/*   Updated: 2020/11/23 12:58:29 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define ROWS 8
#define COLS 8
#define TILE_SIZE 32
#include <mlx.h>
#include <stdlib.h>
#include "key_macos.h"
#include "cub3d.h"

void draw_player(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			game->player.data[i * 9 + j] = game->player.color;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->player.imgptr, game->player.x, game->player.y);
}

void draw_background(t_game *game)
{
	int i;
	int j;

	i = 0;
	while (i < game->background.width)
	{
		j = 0;
		while (j < game->background.height)
		{
			game->background.data[i * game->background.width + j] = game->background.color;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->background.imgptr, 0, 0);
}

void init_player(t_game *game)
{
	game->player.x = 255;
	game->player.y = 255;
	game->player.color = 0xFF0000;
	game->player.imgptr = mlx_new_image(game->mlx, 9, 9);
	game->player.data = (int *)mlx_get_data_addr(game->player.imgptr, &game->player.bpp, &game->player.size_l, &game->player.endian);
	draw_player(game);
}

void init_background(t_game *game)
{
	int i;
	int j;

	game->background.width = 500;
	game->background.height = 500;
	game->background.color = 0x000000;
	game->background.imgptr = mlx_new_image(game->mlx, game->background.width, game->background.height);
	game->background.data = (int *)mlx_get_data_addr(game->background.imgptr, &game->background.bpp, &game->background.size_l, &game->background.endian);
	draw_background(game);
}

int		press_key_for_dot(int key, t_game *game)
{
	if (key == K_A)
		game->player.x -= 5;
	if (key == K_D)
		game->player.x += 5;
	if (key == K_W)
		game->player.y -= 5;
	if (key == K_S)
		game->player.y += 5;
	if (key == K_ESC)
		exit(0);
	draw_background(game);
	draw_player(game);
	return (0);
}

int		main(void)
{
	t_game game;
	game.window.width = 500;
	game.window.height = 500;
	game.mlx = mlx_init();
	game.win = mlx_new_game(game.mlx, game.window.width, game.window.height, "cub3d");
	init_background(&game);
	init_player(&game);
	mlx_hook(game.win, 2, 1, press_key_for_dot, &game);
	mlx_loop(game.mlx);
}
