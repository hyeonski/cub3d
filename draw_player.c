/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:53:34 by hyeonski          #+#    #+#             */
/*   Updated: 2020/11/18 15:15:50 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <stdlib.h>
#include "key_macos.h"
#include "cub3d.h"

void draw_player(t_window *window)
{
	int i;
	int j;

	i = 0;
	while (i < 9)
	{
		j = 0;
		while (j < 9)
		{
			window->player.data[i * 9 + j] = window->player.color;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(window->mlx, window->win, window->player.imgptr, window->player.x, window->player.y);
}

void draw_background(t_window *window)
{
	int i;
	int j;

	i = 0;
	while (i < window->background.width)
	{
		j = 0;
		while (j < window->background.height)
		{
			window->background.data[i * window->background.width + j] = window->background.color;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(window->mlx, window->win, window->background.imgptr, 0, 0);
}

void init_player(t_window *window)
{
	window->player.x = 255;
	window->player.y = 255;
	window->player.color = 0xFF0000;
	window->player.imgptr = mlx_new_image(window->mlx, 9, 9);
	window->player.data = (int *)mlx_get_data_addr(window->player.imgptr, &window->player.bpp, &window->player.size_l, &window->player.endian);
	draw_player(window);
}

void init_background(t_window *window)
{
	int i;
	int j;

	window->background.width = 500;
	window->background.height = 500;
	window->background.color = 0x000000;
	window->background.imgptr = mlx_new_image(window->mlx, window->background.width, window->background.height);
	window->background.data = (int *)mlx_get_data_addr(window->background.imgptr, &window->background.bpp, &window->background.size_l, &window->background.endian);
	draw_background(window);
}

int map[8][8] = 
{
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 1, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
};

void draw_map(t_window *window)
{
	int		i;
	int		j;
	int		x;
	int		y;

	window->map.block_size = window->height / 8;
	window->map.imgptr = mlx_new_image(window->mlx, window->map.block_size, window->map.block_size);
	window->map.data = (int *)mlx_get_data_addr(block, &window->map.bpp, &window->map.size_l, &window->map.endian);

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (map[i][j] == 1)
			{
				window->background.data[i * window->background.width + j] = window->background.color;
			}
		}
	}
}

int		draw_grid(t_window *window)
{
	int	draw_position;
	int	i;

	i = 1;
	while (i < window->row_count)
	{
		draw_position = 0;
		while (draw_position <= window->width){
			mlx_pixel_put(window->mlx, window->win, draw_position, i * (window->height / window->row_count),window->grid_color);
			draw_position++;
		}
		i++;
	}
	i = 1;
	while (i< window->column_count)
	{
		draw_position = 0;
		while (draw_position <= window->width){
			mlx_pixel_put(window->mlx, window->win, i * (window->width/ window->column_count), draw_position,window->grid_color);
			draw_position++;
		}
		i++;
	}
	return (0);
}

int		press_key_for_dot(int key, t_window *window)
{
	if (key == K_A)
		window->player.x -= 5;
	if (key == K_D)
		window->player.x += 5;
	if (key == K_W)
		window->player.y -= 5;
	if (key == K_S)
		window->player.y += 5;
	if (key == K_ESC)
		exit(0);
	draw_background(window);
	draw_player(window);
	return (0);
}

int		main(void)
{
	t_window window;
	window.width = 500;
	window.height = 500;
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, window.width, window.height, "mlx_grid");
	init_background(&window);
	init_player(&window);
	mlx_hook(window.win, 2, 1, press_key_for_dot, &window);
	mlx_loop(window.mlx);
}
