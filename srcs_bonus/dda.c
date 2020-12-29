/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:06:09 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 20:00:50 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void		init_ray(int x, int w, t_ray *ray, t_player *player)
{
	double	camera_x;

	camera_x = 2 * x / (double)w - 1;
	ray->raydir_x = player->dir_x + player->plane_x * camera_x;
	ray->raydir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
}

void		calc_delta_dist(t_ray *ray)
{
	ray->delta_dist_x = fabs(1 / ray->raydir_x);
	ray->delta_dist_y = fabs(1 / ray->raydir_y);
}

void		calc_step_side_dist(t_ray *ray, t_player *player)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x =
			(ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y =
			(ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

void		dda(t_ray *ray)
{
	while (1)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (g_cub.map.data[ray->map_x][ray->map_y] == '1')
			break ;
	}
}

void		calc_perp_wall_dist(t_draw_info *draw_info,
		t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		draw_info->perp_wall_dist =
			(ray->map_x - player->pos_x +
			(1 - ray->step_x) / 2) / ray->raydir_x;
	else
		draw_info->perp_wall_dist =
			(ray->map_y - player->pos_y +
			(1 - ray->step_y) / 2) / ray->raydir_y;
}
