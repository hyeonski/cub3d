/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:50:59 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 20:00:50 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void				get_draw_info(int x, t_draw_info *draw_info,
		t_window *window)
{
	int				height;

	height = window->height;
	init_ray(x, window->width, &draw_info->ray, &g_cub.player);
	calc_delta_dist(&draw_info->ray);
	calc_step_side_dist(&draw_info->ray, &g_cub.player);
	dda(&draw_info->ray);
	calc_perp_wall_dist(draw_info, &draw_info->ray, &g_cub.player);
	draw_info->line_height = (int)(height / draw_info->perp_wall_dist);
	draw_info->draw_start = -draw_info->line_height / 2 + height / 2;
	if (draw_info->draw_start < 0)
		draw_info->draw_start = 0;
	draw_info->draw_end = draw_info->line_height / 2 + height / 2;
	if (draw_info->draw_end >= height)
		draw_info->draw_end = height - 1;
}

void				select_texture(t_tex_info *tex_info,
		t_player *player, t_draw_info *draw_info)
{
	if (draw_info->ray.side == 1)
	{
		tex_info->tex_num = draw_info->ray.raydir_y > 0 ? 0 : 1;
		tex_info->wall_x =
			player->pos_x + draw_info->perp_wall_dist * draw_info->ray.raydir_x;
	}
	else
	{
		tex_info->tex_num = draw_info->ray.raydir_x > 0 ? 2 : 3;
		tex_info->wall_x =
			player->pos_y + draw_info->perp_wall_dist * draw_info->ray.raydir_y;
	}
}

void				get_tex_info(t_tex_info *tex_info, t_draw_info *draw_info,
		t_ray *ray)
{
	select_texture(tex_info, &g_cub.player, draw_info);
	tex_info->wall_x -= floor((tex_info->wall_x));
	tex_info->tex_width = g_cub.texture[tex_info->tex_num].width;
	tex_info->tex_height = g_cub.texture[tex_info->tex_num].height;
	tex_info->tex_x = (int)(tex_info->wall_x * (double)tex_info->tex_width);
	if (ray->side == 0 && ray->raydir_x > 0)
		tex_info->tex_x = tex_info->tex_width - tex_info->tex_x - 1;
	if (ray->side == 1 && ray->raydir_y < 0)
		tex_info->tex_x = tex_info->tex_width - tex_info->tex_x - 1;
	tex_info->step = 1.0 * tex_info->tex_height / draw_info->line_height;
	tex_info->tex_pos =
		(draw_info->draw_start - g_cub.window.height / 2 +
		draw_info->line_height / 2) * tex_info->step;
}

int					get_tex_pixel(t_tex_info *tex_info, t_draw_info *draw_info)
{
	int				tex_y;
	int				position;
	int				color;

	tex_y = (int)tex_info->tex_pos & (tex_info->tex_height - 1);
	position = tex_info->tex_height * tex_y + tex_info->tex_x;
	color = g_cub.texture[tex_info->tex_num].data[position];
	if (draw_info->ray.side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

void				draw_wall(t_cub *cub, t_window *window)
{
	int				x;
	int				y;
	int				color;
	t_draw_info		draw_info;
	t_tex_info		tex_info;

	x = 0;
	while (x < window->width)
	{
		get_draw_info(x, &draw_info, window);
		get_tex_info(&tex_info, &draw_info, &draw_info.ray);
		y = draw_info.draw_start;
		while (y < draw_info.draw_end)
		{
			color = get_tex_pixel(&tex_info, &draw_info);
			window->buf[y][x] = color;
			tex_info.tex_pos += tex_info.step;
			y++;
		}
		cub->z_buffer[x] = draw_info.perp_wall_dist;
		x++;
	}
}
