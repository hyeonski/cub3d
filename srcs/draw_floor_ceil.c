/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:49:09 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/28 18:29:19 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	draw_floor_ceil(t_window *window, t_rgb *floor, t_rgb *ceiling)
{
	int	color;
	int	x;
	int	y;

	y = window->height / 2 + 1;
	while (y < window->height)
	{
		x = 0;
		while (x < window->width)
		{
			color = (floor->r << 16) + (floor->g << 8) + floor->b;
			window->buf[y][x] = color;
			color = (ceiling->r << 16) + (ceiling->g << 8) + ceiling->b;
			window->buf[window->height - y - 1][x] = color;
			x++;
		}
		y++;
	}
}
