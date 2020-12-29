/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceil.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:49:09 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 22:00:07 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void				get_floor_info(t_floor_info *info,
		t_window *window, t_player *player, int y)
{
	info->raydir_x0 = player->dir_x - player->plane_x;
	info->raydir_y0 = player->dir_y - player->plane_y;
	info->raydir_x1 = player->dir_x + player->plane_x;
	info->raydir_y1 = player->dir_y + player->plane_y;
	info->p = y - window->height / 2;
	info->pos_z = 0.5 * window->height;
	info->row_dist = info->pos_z / info->p;
	info->floor_step_x =
		info->row_dist * (info->raydir_x1 - info->raydir_x0) / window->width;
	info->floor_step_y =
		info->row_dist * (info->raydir_y1 - info->raydir_y0) / window->width;
	info->floor_x = player->pos_x + info->row_dist * info->raydir_x0;
	info->floor_y = player->pos_y + info->row_dist * info->raydir_y0;
}

void				get_floor_tex(t_floor_info *info, t_window *window, int y)
{
	int				x;
	int				color;
	int				tex_width;
	int				tex_height;

	tex_width = g_cub.texture[5].width;
	tex_height = g_cub.texture[5].height;
	x = 0;
	while (x < window->width)
	{
		info->cell_x = (int)(info->floor_x);
		info->cell_y = (int)(info->floor_y);
		info->tx =
			(int)(tex_width * (info->floor_x - info->cell_x)) & (tex_width - 1);
		info->ty = (int)(tex_height * (info->floor_y - info->cell_y))
			& (tex_height - 1);
		info->floor_x += info->floor_step_x;
		info->floor_y += info->floor_step_y;
		color = g_cub.texture[6].data[tex_width * info->ty + info->tx];
		window->buf[y][x] = color;
		color = g_cub.texture[5].data[tex_width * info->ty + info->tx];
		window->buf[window->height - y - 1][x] = color;
		x++;
	}
}

void				draw_floor_ceil(t_window *window, t_player *player)
{
	t_floor_info	info;
	int				y;

	load_texture(&g_cub.texture[5], "./textures/ceiling.xpm");
	load_texture(&g_cub.texture[6], "./textures/floor.xpm");
	y = window->height / 2 + 1;
	while (y < window->height)
	{
		get_floor_info(&info, window, player, y);
		get_floor_tex(&info, window, y);
		y++;
	}
}
