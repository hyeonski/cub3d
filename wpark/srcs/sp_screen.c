/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_screen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:17:51 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 15:06:39 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_csp(t_calsp *csp, t_sprite *sp, t_player *p, t_config *conf)
{
	double	sp_x;
	double	sp_y;

	sp_x = sp->x - p->pos->x;
	sp_y = sp->y - p->pos->y;
	csp->inv_det = 1.0 / (p->plane->x * p->dir->y - p->dir->x * p->plane->y);
	csp->trans_x = csp->inv_det * (p->dir->y * sp_x - p->dir->x * sp_y);
	csp->trans_y = csp->inv_det * (-p->plane->y * sp_x + p->plane->x * sp_y);
	csp->sp_screen_x = (conf->res_w / 2) * (1 - csp->trans_x / csp->trans_y);
	csp->sp_h = abs((int)(conf->res_h / csp->trans_y));
	csp->drawstart_y = -csp->sp_h / 2 + conf->res_h / 2;
	if (csp->drawstart_y < 0)
		csp->drawstart_y = 0;
	csp->drawend_y = csp->sp_h / 2 + conf->res_h / 2;
	if (csp->drawend_y >= conf->res_h)
		csp->drawend_y = conf->res_h - 1;
	csp->sp_w = abs((int)(conf->res_h / csp->trans_y));
	csp->drawstart_x = -csp->sp_w / 2 + csp->sp_screen_x;
	if (csp->drawstart_x < 0)
		csp->drawstart_x = 0;
	csp->drawend_x = csp->sp_w / 2 + csp->sp_screen_x;
	if (csp->drawend_x >= conf->res_w)
		csp->drawend_x = conf->res_w - 1;
}

static void	put_csp(int *screen, int stripe, t_calsp *csp, t_cub3d *cub3d)
{
	int			y;
	int			d;
	int			color;
	t_config	*conf;

	conf = cub3d->conf;
	csp->tex_x = (int)(256 * (stripe - (-csp->sp_w / 2 + csp->sp_screen_x))
		* conf->tex->wh[TEX_O][0] / csp->sp_w / 256);
	if (csp->trans_y > 0 && stripe > 0
		&& stripe < conf->res_w
		&& csp->trans_y < cub3d->zbuff[stripe])
	{
		y = csp->drawstart_y;
		csp->tex_w = conf->tex->wh[TEX_O][0];
		while (y < csp->drawend_y)
		{
			d = y * 256 - conf->res_h * 128 + csp->sp_h * 128;
			csp->tex_y = ((d * conf->tex->wh[TEX_O][1]) / csp->sp_h) / 256;
			color = ((int*)conf->tex->data[TEX_O])
				[csp->tex_w * csp->tex_y + csp->tex_x];
			if ((color & 0x00FFFFFF) != 0)
				screen[y * conf->res_w + stripe] = color;
			y++;
		}
	}
}

void		sprite_on_screen(t_cub3d *cub3d)
{
	t_sprite	*sp;
	t_player	*p;
	t_calsp		csp;
	int			stripe;

	sp = cub3d->sp;
	p = cub3d->player;
	while (sp)
	{
		set_csp(&csp, sp, p, cub3d->conf);
		stripe = csp.drawstart_x;
		while (stripe < csp.drawend_x)
		{
			put_csp(cub3d->data, stripe, &csp, cub3d);
			stripe++;
		}
		sp = sp->next;
	}
}
