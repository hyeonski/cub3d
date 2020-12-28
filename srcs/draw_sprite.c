/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:52:45 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/28 18:34:11 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void					calc_draw_sprite_info(t_sprite_info *info,
		t_sprite *sprite)
{
	info->w = g_cub.window.width;
	info->h = g_cub.window.height;
	info->sprite_x = sprite->x - g_cub.player.pos_x;
	info->sprite_y = sprite->y - g_cub.player.pos_y;
	info->inv_det =
		1.0 / (g_cub.player.plane_x * g_cub.player.dir_y -
				g_cub.player.dir_x * g_cub.player.plane_y);
	info->transform_x =
		info->inv_det * (g_cub.player.dir_y * info->sprite_x -
				g_cub.player.dir_x * info->sprite_y);
	info->transform_y =
		info->inv_det * (-g_cub.player.plane_y * info->sprite_x +
				g_cub.player.plane_x * info->sprite_y);
	info->sprite_screen_x =
		(int)((info->w / 2) * (1 + info->transform_x / info->transform_y));
	info->sprite_h =
		abs((int)(info->h / (info->transform_y)));
	calc_draw_sprite_info_sub(info);
}

void					calc_draw_sprite_info_sub(t_sprite_info *info)
{
	info->draw_start_y = -info->sprite_h / 2 + info->h / 2;
	if (info->draw_start_y < 0)
		info->draw_start_y = 0;
	info->draw_end_y = info->sprite_h / 2 + info->h / 2;
	if (info->draw_end_y >= info->h)
		info->draw_end_y = info->h - 1;
	info->sprite_w = abs((int)(info->h / (info->transform_y)));
	info->draw_start_x = -info->sprite_w / 2 + info->sprite_screen_x;
	if (info->draw_start_x < 0)
		info->draw_start_x = 0;
	info->draw_end_x = info->sprite_w / 2 + info->sprite_screen_x;
	if (info->draw_end_x >= info->w)
		info->draw_end_x = info->w - 1;
	info->tex_width = g_cub.texture[4].width;
	info->tex_height = g_cub.texture[4].height;
}

void					draw_ele(t_sprite *sprite)
{
	t_sprite_info		info;
	int					stripe;
	int					temp;

	calc_draw_sprite_info(&info, sprite);
	stripe = info.draw_start_x - 1;
	while (++stripe < info.draw_end_x)
	{
		temp = stripe - (-info.sprite_w / 2 + info.sprite_screen_x);
		info.tex_x = (int)(256 * temp * info.tex_width / info.sprite_w) / 256;
		if (stripe > 0 && stripe < info.w && info.transform_y > 0
			&& info.transform_y < g_cub.z_buffer[stripe])
			draw_ele_sub(&info, sprite, stripe);
	}
}

void					draw_ele_sub(t_sprite_info *info,
		t_sprite *sprite, int stripe)
{
	int					y;
	int					tmp;

	y = info->draw_start_y - 1;
	while (++y < info->draw_end_y)
	{
		info->d = (y) * 256 - info->h * 128 + info->sprite_h * 128;
		info->tex_y = (info->d * info->tex_height) / info->sprite_h / 256;
		tmp = info->tex_width * info->tex_y + info->tex_x;
		info->color = g_cub.texture[sprite->tex_num].data[tmp];
		if ((info->color & 0x00FFFFFF) != 0)
			g_cub.window.buf[y][stripe] = info->color;
	}
}

void					draw_sprite(t_cub *cub)
{
	ft_lstsort(&cub->sprite, compare_sprite_dist);
	ft_lstforeach(cub->sprite, draw_ele);
}
