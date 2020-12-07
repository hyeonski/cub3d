/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:18:14 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 15:56:15 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ceiling_on_screen(t_cub3d *cub3d, t_ray *ray, int *screen)
{
	int y;

	y = 0;
	while (y < ray->draw_start)
	{
		screen[cub3d->conf->res_w * y + ray->now] = cub3d->conf->color_c;
		y++;
	}
}

void		floor_on_screen(t_cub3d *cub3d, t_ray *ray, int *screen)
{
	int y;

	y = ray->draw_end;
	while (y < cub3d->conf->res_h)
	{
		screen[cub3d->conf->res_w * y + ray->now] = cub3d->conf->color_f;
		y++;
	}
}

static void	calc_wall(t_calwall *cw, t_tex *tex, t_ray *ray, t_player *p)
{
	if (ray->is_side == 1)
		cw->wall_x = p->pos->y + ray->dist * ray->dir->y;
	else
		cw->wall_x = p->pos->x + ray->dist * ray->dir->x;
	cw->wall_x -= floor(cw->wall_x);
	cw->tex_x = (int)(cw->wall_x * (double)(tex->wh[ray->wall_type][0]));
	if (ray->is_side == 1 && ray->dir->x > 0)
		cw->tex_x = tex->wh[ray->wall_type][0] - cw->tex_x - 1;
	else if (ray->is_side == 0 && ray->dir->y < 0)
		cw->tex_x = tex->wh[ray->wall_type][0] - cw->tex_x - 1;
}

void		wall_on_screen(t_cub3d *cub3d, t_tex *tex, t_ray *ray, int *screen)
{
	int			y;
	int			d;
	int			*data;
	t_calwall	cw;

	calc_wall(&cw, tex, ray, cub3d->player);
	data = tex->data[ray->wall_type];
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		d = y * 256 - cub3d->conf->res_h * 128 + ray->wall_h * 128;
		cw.tex_y = ((d * tex->wh[ray->wall_type][1]) / ray->wall_h) / 256;
		if (cw.tex_y > tex->wh[ray->wall_type][1])
			cw.tex_y = tex->wh[ray->wall_type][1] - 1;
		if (cw.tex_y < 0)
			cw.tex_y = 0;
		screen[cub3d->conf->res_w * y + ray->now] =
			data[tex->wh[ray->wall_type][0] * cw.tex_y + cw.tex_x];
		y++;
	}
}

int			set_screen(t_cub3d *cub3d)
{
	if (!(cub3d->mlx = mlx_init()))
		return (err_free(-1, "Failed to init mlx.\n", cub3d, 0));
	if (!(cub3d->win = mlx_new_window(cub3d->mlx,
		cub3d->conf->res_w, cub3d->conf->res_h, "cub3d")))
		return (err_free(-1, "Failed to create mlx window.\n", cub3d, 0));
	if (!(cub3d->img = mlx_new_image(cub3d->mlx,
		cub3d->conf->res_w, cub3d->conf->res_h)))
		return (err_free(-1, "Failed to init screen buffer.\n", cub3d, 0));
	if (!(cub3d->data = mlx_get_data_addr(cub3d->img,
		&cub3d->bpp, &cub3d->size_line, &cub3d->endian)))
	{
		return (err_free(-1,
			"Failed to get data from screen buffer.\n", cub3d, 0));
	}
	return (1);
}
