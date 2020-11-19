/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 15:53:34 by hyeonski          #+#    #+#             */
/*   Updated: 2020/11/17 21:08:41 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "key_macos.h"

typedef struct	s_player
{
	int			x;
	int			y;
	int			color;
}				t_player;

typedef struct	s_window
{
	void	*mlx;
	void	*win;
	t_player player;

	int		width;
	int		height;

	int		row_count;
	int		column_count;
	int		grid_color;
}				t_window;

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

void	init_player(t_window *window)
{
	int x;
	int y;
	int color;

	x = window->player.x;
	y = window->player.y;
	mlx_pixel_put(window->mlx, window->win, x, y, color);
	mlx_pixel_put(window->mlx, window->win, x + 1, y, color);
	mlx_pixel_put(window->mlx, window->win, x + 1, y + 1, color);
	mlx_pixel_put(window->mlx, window->win, x, y + 1, color);
}

void	move_dot_left(t_window *window)
{
	int	old_x = window->player.x;
	int old_y = window->player.y;
	int	black = 0x000000;

	if ((0 < window->player.x && window->player.x <= window->width) &&
		(0 < window->player.y && window->player.x <= window->height))
	{
		mlx_pixel_put(window->mlx, window->win, old_x + 1, old_y, black);
		mlx_pixel_put(window->mlx, window->win, old_x + 1, old_y + 1, black);
		mlx_pixel_put(window->mlx, window->win, --window->player.x, window->player.y, window->player.color);
		mlx_pixel_put(window->mlx, window->win, window->player.x, window->player.y + 1, window->player.color);
	}
}

void	move_dot_right(t_window *window)
{
	int	old_x = window->player.x;
	int old_y = window->player.y;
	int	black = 0x000000;

	if ((0 < window->player.x && window->player.x <= window->width) &&
		(0 < window->player.y && window->player.x <= window->height))
	{
		mlx_pixel_put(window->mlx, window->win, old_x, old_y, black);
		mlx_pixel_put(window->mlx, window->win, old_x, old_y + 1, black);
		window->player.x++;
		mlx_pixel_put(window->mlx, window->win, window->player.x + 1, window->player.y, window->player.color);
		mlx_pixel_put(window->mlx, window->win, window->player.x + 1, window->player.y + 1, window->player.color);
	}
}
void	move_dot_down(t_window *window)
{
	int	old_x = window->player.x;
	int old_y = window->player.y;
	int	black = 0x000000;

	if ((0 < window->player.x && window->player.x <= window->width) &&
		(0 < window->player.y && window->player.x <= window->height))
	{
		mlx_pixel_put(window->mlx, window->win, old_x, old_y, black);
		mlx_pixel_put(window->mlx, window->win, old_x + 1, old_y, black);
		window->player.y++;
		mlx_pixel_put(window->mlx, window->win, window->player.x, window->player.y + 1, window->player.color);
		mlx_pixel_put(window->mlx, window->win, window->player.x + 1, window->player.y + 1, window->player.color);
	}
}

void	move_dot_up(t_window *window)
{
	int	old_x = window->player.x;
	int old_y = window->player.y;
	int	black = 0x000000;

	if ((0 < window->player.x && window->player.x <= window->width) &&
		(0 < window->player.y && window->player.x <= window->height))
	{
		mlx_pixel_put(window->mlx, window->win, old_x + 1, old_y + 1, black);
		mlx_pixel_put(window->mlx, window->win, old_x, old_y + 1, black);
		window->player.y--;
		mlx_pixel_put(window->mlx, window->win, window->player.x, window->player.y, window->player.color);
		mlx_pixel_put(window->mlx, window->win, window->player.x + 1, window->player.y, window->player.color);
	}
}

int		press_key_for_dot(int key, t_window *window)
{
	if (key == K_A)
		move_dot_left(window);
	else if (key == K_D)
		move_dot_right(window);
	else if (key == K_W)
		move_dot_up(window);
	else if (key == K_S)
		move_dot_down(window);
	return (0);
}

int		main(void)
{
	t_window window;
	window.width = 500;
	window.height = 500;
	window.row_count = 10;
	window.column_count = 10;
	window.grid_color = 0xFFFFFF;
	window.player.color = 0xFF0000;
	window.player.x = 220;
	window.player.y = 220;
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, window.width, window.height, "mlx_grid");
	init_player(&window);
	mlx_loop_hook(window.mlx, draw_grid, &window);
	mlx_hook(window.win, 2, 1, press_key_for_dot, &window);
	mlx_loop(window.mlx);
}
