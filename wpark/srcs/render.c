/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:18:28 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 14:50:22 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		calc_side_dist(t_pos *side, t_pos *delta, int map[], int step[])
{
	if (side->x < side->y)
	{
		side->x += delta->x;
		map[0] += step[0];
		return (1);
	}
	else
	{
		side->y += delta->y;
		map[1] += step[1];
		return (0);
	}
}

double	deg2rad(double deg)
{
	return (deg / 180 * M_PI);
}

void	render(t_cub3d *cub3d)
{
	mlx_put_image_to_window(cub3d->mlx, cub3d->win, cub3d->img, 0, 0);
}
