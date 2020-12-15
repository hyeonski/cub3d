#include "includes/cub3d.h"

void	init_ray(int x, int w, t_ray *ray, t_player *player)
{
	double camera_x;
	
	camera_x = 2 * x / (double)w - 1;
	ray->raydir_x = player->dir_x + player->plane_x * camera_x;
	ray->raydir_y = player->dir_y + player->plane_y * camera_x;
	ray->map_x = (int)player->pos_x;
	ray->map_y = (int)player->pos_y;
}

void	calc_delta_dist(t_ray *ray)
{
	ray->delta_dist_x = fabs(1 / ray->raydir_x);
	ray->delta_dist_y = fabs(1 / ray->raydir_y);
}

void	calc_step_side_dist(t_ray *ray, t_player *player)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos_x) * ray->delta_dist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos_y) * ray->delta_dist_y;
	}
}

void	calc_perp_wall_dist(t_draw_info *draw_info)
{
	if (draw_info->ray.side == 0)
		draw_info->perp_wall_dist = (draw_info->ray.map_x - g_cub.player.pos_x + (1 - draw_info->ray.step_x) / 2) / draw_info->ray.raydir_x;
	else
		draw_info->perp_wall_dist = (draw_info->ray.map_y - g_cub.player.pos_y + (1 - draw_info->ray.step_y) / 2) / draw_info->ray.raydir_y;
}

void	draw_wall(t_window *window)
{
	int x;
	int y;
	int color;
	t_draw_info		draw_info;
	t_tex_info		tex_info;

	x = 0;
	while (x < window->width)
	{
		init_ray(x, window->width, &draw_info.ray, &g_cub.player);
		calc_delta_dist(&draw_info.ray);
		int hit = 0;
		calc_step_side_dist(&draw_info.ray, &g_cub.player);
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (draw_info.ray.side_dist_x < draw_info.ray.side_dist_y)
			{
				draw_info.ray.side_dist_x += draw_info.ray.delta_dist_x;
				draw_info.ray.map_x += draw_info.ray.step_x;
				draw_info.ray.side = 0;
			}
			else
			{
				draw_info.ray.side_dist_y += draw_info.ray.delta_dist_y;
				draw_info.ray.map_y += draw_info.ray.step_y;
				draw_info.ray.side = 1;
			}
			//Check if ray has hit a wall
			if (g_cub.map.data[draw_info.ray.map_x][draw_info.ray.map_y] > 0)
				hit = 1;
		}
		calc_perp_wall_dist(&draw_info);
		draw_info.line_height = (int)(window->height / draw_info.perp_wall_dist);
		draw_info.draw_start = -draw_info.line_height / 2 + window->height / 2;
		if (draw_info.draw_start < 0)
			draw_info.draw_start = 0;
		draw_info.draw_end = draw_info.line_height / 2 + window->height / 2;
		if (draw_info.draw_end >= window->height)
			draw_info.draw_end = window->height - 1;
		if (draw_info.ray.side == 1)
			tex_info.tex_num = draw_info.ray.raydir_y > 0 ? 0 : 1;
		else
			tex_info.tex_num = draw_info.ray.raydir_x > 0 ? 2 : 3;
		if (draw_info.ray.side == 0)
			tex_info.wall_x = g_cub.player.pos_y + draw_info.perp_wall_dist * draw_info.ray.raydir_y;
		else
			tex_info.wall_x = g_cub.player.pos_x + draw_info.perp_wall_dist * draw_info.ray.raydir_x;
		tex_info.wall_x -= floor((tex_info.wall_x));
		tex_info.tex_width = g_cub.texture[tex_info.tex_num].width;
		tex_info.tex_height = g_cub.texture[tex_info.tex_num].height;
		tex_info.tex_x = (int)(tex_info.wall_x * (double)tex_info.tex_width);
		if(draw_info.ray.side == 0 && draw_info.ray.raydir_x > 0)
			tex_info.tex_x = tex_info.tex_width - tex_info.tex_x - 1;
		if(draw_info.ray.side == 1 && draw_info.ray.raydir_y < 0)
			tex_info.tex_x = tex_info.tex_width - tex_info.tex_x - 1;
		tex_info.step = 1.0 * tex_info.tex_height / draw_info.line_height;
		tex_info.tex_pos = (draw_info.draw_start - window->height / 2 + draw_info.line_height / 2) * tex_info.step;
		y = draw_info.draw_start;
		while (y < draw_info.draw_end)
		{
			int texY = (int)tex_info.tex_pos & (tex_info.tex_height - 1);
			tex_info.tex_pos += tex_info.step;
			color = g_cub.texture[tex_info.tex_num].data[tex_info.tex_height * texY + tex_info.tex_x];
			if (draw_info.ray.side == 1)
				color = (color >> 1) & 8355711;
			window->buf[y][x] = color;
			y++;
		}
		g_cub.zBuffer[x] = draw_info.perp_wall_dist; 
	}