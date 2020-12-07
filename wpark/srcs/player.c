/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:18:44 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 14:29:37 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_pos(t_pos *pos, double x, double y)
{
	pos->x = x;
	pos->y = y;
}

void	rotate_pos(t_pos *pos, double rad)
{
	double	rot_x;
	double	rot_y;

	rot_x = cos(rad) * pos->x - sin(rad) * pos->y;
	rot_y = sin(rad) * pos->x + cos(rad) * pos->y;
	set_pos(pos, rot_x, rot_y);
}

int		move_player(t_cub3d *cub3d)
{
	double		new_x;
	double		new_y;
	t_player	*p;

	p = cub3d->player;
	new_x = p->pos->x + p->dir->x * p->mov_speed * p->mov_dir;
	new_y = p->pos->y + p->dir->y * p->mov_speed * p->mov_dir;
	if (!(is_wall((int)new_x, (int)new_y, cub3d)))
		set_pos(p->pos, new_x, new_y);
	return (1);
}

int		rotate_player(t_cub3d *cub3d)
{
	t_player	*p;
	double		rot_rad;

	p = cub3d->player;
	rot_rad = deg2rad(p->rot_dir * p->rot_speed);
	rotate_pos(cub3d->player->dir, rot_rad);
	rotate_pos(cub3d->player->plane, rot_rad);
	return (1);
}
