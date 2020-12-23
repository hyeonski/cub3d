/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:51:47 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/23 21:50:04 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define numSprites 19

t_cub	g_cub;

void	key_update(void);

void	update_screen(t_cub *cub, t_window *window)
{
	for (int y = 0; y < window->height; y++)
	{
		for (int x = 0; x < window->width; x++)
		{
			cub->data[y * window->width + x] = window->buf[y][x];
		}
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgptr, 0, 0);
}

void	draw_floor_ceil(t_window *window, t_rgb *floor, t_rgb *ceiling)
{
	int color;
	
	for(int y = window->height / 2 + 1; y < window->height; ++y)
	{
		for(int x = 0; x < window->width; ++x)
		{			
			color = (floor->r << 16) + (floor->g << 8) + floor->b;
			window->buf[y][x] = color;
			color = (ceiling->r << 16) + (ceiling->g << 8) + ceiling->b;
			window->buf[window->height - y - 1][x] = color;
		}
	}

}

int		get_tex_pixel(t_tex_info *tex_info, t_draw_info *draw_info)
{
	int tex_y;
	int position;
	int color;

	tex_y = (int)tex_info->tex_pos & (tex_info->tex_height - 1);
	position = tex_info->tex_height * tex_y + tex_info->tex_x;
	color = g_cub.texture[tex_info->tex_num].data[position];
	if (draw_info->ray.side == 1)
		color = (color >> 1) & 8355711;
	return (color);
}

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

void	dda(t_ray *ray)
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

void	calc_perp_wall_dist(t_draw_info *draw_info, t_ray *ray, t_player *player)
{
	if (ray->side == 0)
		draw_info->perp_wall_dist = (ray->map_x - player->pos_x + (1 - ray->step_x) / 2) / ray->raydir_x;
	else
		draw_info->perp_wall_dist = (ray->map_y - player->pos_y + (1 - ray->step_y) / 2) / ray->raydir_y;
}

void	get_draw_info(int x, t_draw_info *draw_info, t_window *window)
{
	int			height;

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

void	select_texture(t_tex_info *tex_info, t_player *player, t_draw_info *draw_info)
{
	if (draw_info->ray.side == 1)
	{
		tex_info->tex_num = draw_info->ray.raydir_y > 0 ? 0 : 1;
		tex_info->wall_x = player->pos_x + draw_info->perp_wall_dist * draw_info->ray.raydir_x;
	}
	else
	{
		tex_info->tex_num = draw_info->ray.raydir_x > 0 ? 2 : 3;
		tex_info->wall_x = player->pos_y + draw_info->perp_wall_dist * draw_info->ray.raydir_y;
	}
}

void	get_tex_info(t_tex_info *tex_info, t_draw_info *draw_info, t_ray *ray)
{
	select_texture(tex_info, &g_cub.player, draw_info);
	tex_info->wall_x -= floor((tex_info->wall_x));
	tex_info->tex_width = g_cub.texture[tex_info->tex_num].width;
	tex_info->tex_height = g_cub.texture[tex_info->tex_num].height;
	tex_info->tex_x = (int)(tex_info->wall_x * (double)tex_info->tex_width);
	if(ray->side == 0 && ray->raydir_x > 0)
		tex_info->tex_x = tex_info->tex_width - tex_info->tex_x - 1;
	if(ray->side == 1 && ray->raydir_y < 0)
		tex_info->tex_x = tex_info->tex_width - tex_info->tex_x - 1;
	tex_info->step = 1.0 * tex_info->tex_height / draw_info->line_height;
	tex_info->tex_pos = (draw_info->draw_start - g_cub.window.height / 2 + draw_info->line_height / 2) * tex_info->step;

}

void	draw_wall(t_cub *cub, t_window *window)
{
	int x;
	int y;
	int color;
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
		cub->zBuffer[x] = draw_info.perp_wall_dist; 
		x++;
	}
}

int		compare(t_sprite *lhs, t_sprite *rhs)
{
	int lhs_dist;
	int rhs_dist;

	lhs_dist = pow(lhs->x - g_cub.player.pos_x, 2)
				+ pow(lhs->y - g_cub.player.pos_y, 2);
	rhs_dist = pow(rhs->x - g_cub.player.pos_x, 2)
				+ pow(rhs->y - g_cub.player.pos_y, 2);
	return (lhs_dist < rhs_dist);
}

void	calc_draw_sprite_info_sub(t_sprite_info *info)
{
	info->draw_start_y = -info->sprite_h / 2 + info->h / 2;
	if (info->draw_start_y < 0)
		info->draw_start_y = 0;
	info->draw_end_y = info->sprite_h / 2 + info->h / 2;
	if (info->draw_end_y >= info->h)
		info->draw_end_y = info->h - 1;
	info->sprite_w = abs((int)(info->h / (info->transform_y)));
	info->draw_start_x = -info->sprite_w / 2 + info->sprite_screen_x;
	if(info->draw_start_x < 0)
		info->draw_start_x = 0;
	info->draw_end_x = info->sprite_w / 2 + info->sprite_screen_x;
	if(info->draw_end_x >= info->w)
		info->draw_end_x = info->w - 1;
	info->tex_width = g_cub.texture[4].width;
	info->tex_height = g_cub.texture[4].height;
}

void	calc_draw_sprite_info(t_sprite_info *info, t_sprite *sprite)
{
	info->w = g_cub.window.width;
	info->h = g_cub.window.height;
	info->sprite_x = sprite->x - g_cub.player.pos_x;
	info->sprite_y = sprite->y - g_cub.player.pos_y;
	info->inv_det = 1.0 / (g_cub.player.plane_x * g_cub.player.dir_y -
							g_cub.player.dir_x * g_cub.player.plane_y);
	info->transform_x = info->inv_det * (g_cub.player.dir_y * info->sprite_x
									- g_cub.player.dir_x * info->sprite_y);
	info->transform_y = info->inv_det * (-g_cub.player.plane_y * info->sprite_x
									+ g_cub.player.plane_x * info->sprite_y);
	info->sprite_screen_x = (int)((info->w / 2)
								* (1 + info->transform_x / info->transform_y));
	info->sprite_h = abs((int)(info->h / (info->transform_y)));
	calc_draw_sprite_info_sub(info);
}

void	draw_ele_sub(t_sprite_info *info, t_sprite *sprite, int stripe)
{
	int y;
	int tmp;

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

void	draw_ele(t_sprite *sprite)
{
	t_sprite_info	info;
	int					stripe;
	int					temp;

	calc_draw_sprite_info(&info, sprite);
	stripe = info.draw_start_x - 1;
	while (++stripe < info.draw_end_x)
	{
		temp = stripe - (-info.sprite_w / 2 + info.sprite_screen_x);
		info.tex_x = (int)(256 * temp * info.tex_width / info.sprite_w) / 256;
		if (stripe > 0 && stripe < info.w && info.transform_y > 0
			&& info.transform_y < g_cub.zBuffer[stripe])
			draw_ele_sub(&info, sprite, stripe);
	}
}

void	draw_sprite(t_cub *cub)
{
	ft_lstsort(&cub->sprite, compare);
	ft_lstforeach(cub->sprite, draw_ele);
}


int	main_loop(t_cub *cub)
{
	draw_floor_ceil(&cub->window, &cub->floor, &cub->ceiling);
	draw_wall(cub, &cub->window);
	draw_sprite(cub);
	update_screen(cub, &cub->window);
	update_player_rotation(&cub->player, &cub->map);
	return (0);
}

void	update_player_rotation(t_player *player, t_map *map)
{
	double old_dir_x;
	double old_plane_x;

	if (g_cub.control.keyboard[KEY_W])
	{
		if (map->data[(int)(player->pos_x + player->dir_x * player->move_speed)][(int)(player->pos_y)] == '0')
			player->pos_x += player->dir_x * player->move_speed;
		if (map->data[(int)(player->pos_x)][(int)(player->pos_y + player->dir_y * player->move_speed)] == '0')
			player->pos_y += player->dir_y * player->move_speed;
	}
	if (g_cub.control.keyboard[KEY_S])
	{
		if (map->data[(int)(player->pos_x - player->dir_x * player->move_speed)][(int)(player->pos_y)] == '0')
			player->pos_x -= player->dir_x * player->move_speed;
		if (map->data[(int)(player->pos_x)][(int)(player->pos_y - player->dir_y * player->move_speed)] == '0')
			player->pos_y -= player->dir_y * player->move_speed;
	}
	if (g_cub.control.keyboard[KEY_D])
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(-player->rot_speed) - player->dir_y * sin(-player->rot_speed);
		player->dir_y = old_dir_x * sin(-player->rot_speed) + player->dir_y * cos(-player->rot_speed);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(-player->rot_speed) - player->plane_y * sin(-player->rot_speed);
		player->plane_y = old_plane_x * sin(-player->rot_speed) + player->plane_y * cos(-player->rot_speed);
	}
	if (g_cub.control.keyboard[KEY_A])
	{
		old_dir_x = player->dir_x;
		player->dir_x = player->dir_x * cos(player->rot_speed) - player->dir_y * sin(player->rot_speed);
		player->dir_y = old_dir_x * sin(player->rot_speed) + player->dir_y * cos(player->rot_speed);
		old_plane_x = player->plane_x;
		player->plane_x = player->plane_x * cos(player->rot_speed) - player->plane_y * sin(player->rot_speed);
		player->plane_y = old_plane_x * sin(player->rot_speed) + player->plane_y * cos(player->rot_speed);
	}
}

void		init_game(t_cub *cub)
{
	int		temp;

	cub->player.move_speed = 0.05;
	cub->player.rot_speed = 0.025;
	
	cub->win = mlx_new_window(cub->mlx, cub->window.width, cub->window.height, "mlx");

	cub->imgptr = mlx_new_image(cub->mlx, cub->window.width, cub->window.height);
	cub->data = (int *)mlx_get_data_addr(cub->imgptr, &temp, &temp, &temp);

	mlx_loop_hook(cub->mlx, &main_loop, cub);
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, 0, &key_press, &cub->control);
	mlx_hook(cub->win, X_EVENT_KEY_RELEASE, 0, &key_release, &cub->control);

	mlx_loop(cub->mlx);
}

int		main(int ac, char **av)
{
	ac += 0;
	g_cub.mlx = mlx_init();
	// if (argc > 3 || argc == 1
	// 	|| (argc == 3 && ft_strcmp("--save", argv[2]) != 0))
	// 	return (print_error(cuberror(invalid_argument)));
	if (!set_cub(av[1]))
		return (-1);
	// if (argc == 3)
	// {
	// 	update_scene();
	// 	save_image_to_bmp_file(g_cub.window.scene, g_cub.window.width,
	// 							g_cub.window.height);
	// }
	// else
	init_game(&g_cub);

	return (0);
}
