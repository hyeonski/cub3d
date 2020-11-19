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
#include "key_macos.h"

typedef struct  s_player
{
    int			x;
	int			y;
	int			color;

	void		*imgptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_player;

typedef struct	s_background
{
	int			width;
	int			height;
	int			color;

	void		*imgptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_background;

typedef struct	s_window
{
	void            *mlx;
	void            *win;
	t_player        player;
    t_background    background;   

	int		width;
	int		height;

	int		row_count;
	int		column_count;
	int		grid_color;
}				t_window;

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
			window->player.data[i * 9 + j] = 0xFF0000;
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(window->mlx, window->win, window->player.imgptr, window->player.x, window->player.y);
}

void init_player(t_window *window)
{
	int i;
	int j;

	window->player.x = 255;
	window->player.y = 255;
	window->player.color = 0xFF0000;
	window->player.imgptr = mlx_new_image(window->mlx, 9, 9);
	window->player.data = (int *)mlx_get_data_addr(window->player.imgptr, &window->player.bpp, &window->player.size_l, &window->player.endian);
	draw_player(window);
}

int		main(void)
{
	t_window window;
	window.width = 500;
	window.height = 500;
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, window.width, window.height, "mlx_grid");
	init_player(&window);
	mlx_loop(window.mlx);
}
