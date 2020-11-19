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

typedef struct s_window
{
	void		*mlx;
	void		*win;
	t_player	player;

	int			width;
	int			height;

	int			row_count;
	int			column_count;
	int			grid_color;
}				t_window;

int		main(void)
{
	t_window window;
	window.width = 500;
	window.height = 500;
	window.mlx = mlx_init();
	window.win = mlx_new_window(window.mlx, window.width, window.height, "mlx_grid");
	mlx_loop(window.mlx);
}
