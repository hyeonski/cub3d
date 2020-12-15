/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:18:33 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 14:48:12 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	set_ray_wallinfo(t_cub3d *cub3d, t_ray *ray, int step[], int is_side)
{
	if (is_side == 1 && step[0] < 0)
		ray->wall_type = TEX_W;
	else if (is_side == 1 && step[0] > 0)
		ray->wall_type = TEX_E;
	else if (is_side == 0 && step[1] < 0)
		ray->wall_type = TEX_N;
	else if (is_side == 0 && step[1] > 0)
		ray->wall_type = TEX_S;
	ray->wall_h = (int)(cub3d->conf->res_h / ray->dist);
	ray->is_side = is_side;
	ray->draw_start = -ray->wall_h / 2 + cub3d->conf->res_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->wall_h / 2 + cub3d->conf->res_h / 2;
	if (ray->draw_end >= cub3d->conf->res_h)
		ray->draw_end = cub3d->conf->res_h - 1;
}

static void
	dda(t_cub3d *cub3d, t_pos *side, t_pos *delta, int step[])
{
	t_ray	*ray;
	int		map[2];
	int		is_side;
	int		hit;

	ray = cub3d->ray;
	map[0] = (int)(cub3d->player->pos->x);
	map[1] = (int)(cub3d->player->pos->y);
	hit = 0;
	while (hit != 1)
	{
		is_side = calc_side_dist(side, delta, map, step);
		hit = is_wall(map[0], map[1], cub3d);
	}
	if (is_side == 1)
		ray->dist =
			(map[0] - cub3d->player->pos->x + (1 - step[0]) / 2) / ray->dir->x;
	else
		ray->dist =
			(map[1] - cub3d->player->pos->y + (1 - step[1]) / 2) / ray->dir->y;
	set_ray_wallinfo(cub3d, ray, step, is_side);
}

static void
	get_side_distance(t_cub3d *cub3d, t_pos *side, t_pos *delta, int step[])
{
	t_pos	*p_pos;
	t_pos	*raydir;
	int		ix;
	int		iy;

	p_pos = cub3d->player->pos;
	raydir = cub3d->ray->dir;
	ix = (int)(p_pos->x);
	iy = (int)(p_pos->y);
	if (raydir->x < 0 && (step[0] = -1))
		side->x = (p_pos->x - ix) * delta->x;
	else if (raydir->x >= 0 && (step[0] = 1))
		side->x = (ix + 1.0 - p_pos->x) * delta->x;
	if (raydir->y < 0 && (step[1] = -1))
		side->y = (p_pos->y - iy) * delta->y;
	else if (raydir->y >= 0 && (step[1] = 1))
		side->y = (iy + 1.0 - p_pos->y) * delta->y;
}

static void
	set_rayinfo(t_cub3d *cub3d, t_ray *ray)
{
	t_pos	side;
	t_pos	delta;
	int		step[2];

	set_pos(&delta, fabs(1 / ray->dir->x), fabs(1 / ray->dir->y));
	get_side_distance(cub3d, &side, &delta, step);
	dda(cub3d, &side, &delta, step);
	cub3d->zbuff[ray->now] = ray->dist;
}

int
	raycasting(t_cub3d *cub3d)
{
	t_player	*p;
	double		cam_x;
	int			i;

	i = 0;
	p = cub3d->player;
	while (i < cub3d->conf->res_w)
	{
		cub3d->ray->now = i;
		cam_x = 1 - 2 * i / (double)(cub3d->conf->res_w);
		set_pos(cub3d->ray->dir,
			p->dir->x + p->plane->x * cam_x, p->dir->y + p->plane->y * cam_x);
		set_rayinfo(cub3d, cub3d->ray);
		ceiling_on_screen(cub3d, cub3d->ray, cub3d->data);
		wall_on_screen(cub3d, cub3d->conf->tex, cub3d->ray, cub3d->data);
		floor_on_screen(cub3d, cub3d->ray, cub3d->data);
		i++;
	}
	sp_update_by_dist(&cub3d->sp, cub3d->player->pos);
	sprite_on_screen(cub3d);
	return (0);
}
