/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:51:47 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/14 22:10:47 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define X_EVENT_KEY_PRESS	2
#define X_EVENT_KEY_RELEASE	3
#define X_EVENT_KEY_EXIT	17
#define numSprites 19

t_cub	g_cub;

/*struct	Sprite
{
	double		x;
	double		y;
	int			texture;
};

struct Sprite	sprite[numSprites] =
{
	{20.5, 11.5, 10}, //green light in front of playerstart
	//green lights in every room
	{18.5,4.5, 10},
	{10.0,4.5, 10},
	{10.0,12.5,10},
	{3.5, 6.5, 10},
	{3.5, 20.5,10},
	{3.5, 14.5,10},
	{14.5,20.5,10},

	//row of pillars in front of wall: fisheye test
	{18.5, 10.5, 9},
	{18.5, 11.5, 9},
	{18.5, 12.5, 9},

	//some barrels around the map
	{21.5, 1.5, 8},
	{15.5, 1.5, 8},
	{16.0, 1.8, 8},
	{16.2, 1.2, 8},
	{3.5,  2.5, 8},
	{9.5, 15.5, 8},
	{10.0, 15.1,8},
	{10.5, 15.8,8},
};

int		spriteOrder[numSprites];
double	spriteDistance[numSprites];

typedef struct		s_pair
{
	double	first;
	int		second;
}					t_pair;
*/

void	key_update(void);

// static int	compare(const void *first, const void *second)
// {
// 	if (*(int *)first > *(int *)second)
// 		return (1);
// 	else if (*(int *)first < *(int *)second)
// 		return (-1);
// 	else
// 		return (0);
// }

// void	sort_order(t_pair *orders, int amount)
// {
// 	t_pair	tmp;

// 	for (int i = 0; i < amount; i++)
// 	{
// 		for (int j = 0; j < amount - 1; j++)
// 		{
// 			if (orders[j].first > orders[j + 1].first)
// 			{
// 				tmp.first = orders[j].first;
// 				tmp.second = orders[j].second;
// 				orders[j].first = orders[j + 1].first;
// 				orders[j].second = orders[j + 1].second;
// 				orders[j + 1].first = tmp.first;
// 				orders[j + 1].second = tmp.second;
// 			}
// 		}
// 	}
// }

void	sort_sprite(int *order, double *dist, int amount)
{
	t_pair	*sprites;

	//std::vector<std::pair<double, int>> sprites(amount);
	sprites = (t_pair*)malloc(sizeof(t_pair) * amount);
	for (int i = 0; i < amount; i++)
	{
		sprites[i].first = dist[i];
		sprites[i].second = order[i];
	}
	sort_order(sprites, amount);
	//std::sort(sprites.begin(), sprites.end());
	for (int i = 0; i < amount; i++)
	{
		dist[i] = sprites[amount - i - 1].first;
		order[i] = sprites[amount - i - 1].second;
	}
	free(sprites);
}

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
		// // rayDir for leftmost ray (x = 0) and rightmost ray (x = w)
		// float rayDirX0 = g_cub.player.dirX - g_cub.player.planeX;
		// float rayDirY0 = g_cub.player.dirY - g_cub.player.planeY;
		// float rayDirX1 = g_cub.player.dirX + g_cub.player.planeX;
		// float rayDirY1 = g_cub.player.dirY + g_cub.player.planeY;
		// // Current y position compared to the center of the screen (the horizon)
		// int p = y - window->height / 2;
		// // Vertical position of the camera.
		// float posZ = 0.5 * window->height;
		// // Horizontal distance from the camera to the floor for the current row.
		// // 0.5 is the z position exactly in the middle between floor and ceiling.
		// float rowDistance = posZ / p;
		// // calculate the real world step vector we have to add for each x (parallel to camera plane)
		// // adding step by step avoids multiplications with a weight in the inner loop
		// float floorStepX = rowDistance * (rayDirX1 - rayDirX0) / window->width;
		// float floorStepY = rowDistance * (rayDirY1 - rayDirY0) / window->width;
		// // real world coordinates of the leftmost column. This will be updated as we step to the right.
		// float floorX = g_cub.player.posX + rowDistance * rayDirX0;
		// float floorY = g_cub.player.posY + rowDistance * rayDirY0;
		// for(int x = 0; x < window->width; ++x)
		// {
		// 	// the cell coord is simply got from the integer parts of floorX and floorY
		// 	int cellX = (int)(floorX);
		// 	int cellY = (int)(floorY);
		// 	// get the texture coordinate from the fractional part
		// 	int tx = (int)(texWidth * (floorX - cellX)) & (texWidth - 1);
		// 	int ty = (int)(texHeight * (floorY - cellY)) & (texHeight - 1);
		// 	floorX += floorStepX;
		// 	floorY += floorStepY;
		// 	// choose texture and draw the pixel
		// 	int checkerBoardPattern = (int)(cellX + cellY) & 1;
		// 	int floorTexture;
		// 	if(checkerBoardPattern == 0) floorTexture = 3;
		// 	else floorTexture = 4;
		// 	int ceilingTexture = 6;
		// 	int color;
		// 	// floor
		// 	color = g_cub.texture[floorTexture][texWidth * ty + tx];
		// 	color = (color >> 1) & 8355711; // make a bit darker
		// 	window->buf[y][x] = color;
		// 	//ceiling (symmetrical, at height - y - 1 instead of y)
		// 	color = g_cub.texture[ceilingTexture][texWidth * ty + tx];
		// 	color = (color >> 1) & 8355711; // make a bit darker
		// 	window->buf[window->height - y - 1][x] = color;
		// }
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

void	draw_sprite(t_cub *cub)
{
	//SPRITE CASTING
	//sort sprites from far to close
	for(int i = 0; i < numSprites; i++)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((g_cub.posX - sprite[i].x) * (g_cub.posX - sprite[i].x) + (g_cub.posY - sprite[i].y) * (g_cub.posY - sprite[i].y)); //sqrt not taken, unneeded
	}
	sortSprites(spriteOrder, spriteDistance, numSprites);
	//after sorting the sprites, do the projection and draw them
	for(int i = 0; i < numSprites; i++)
	{
		//translate sprite position to relative to camera
		double spriteX = sprite[spriteOrder[i]].x - g_cub.posX;
		double spriteY = sprite[spriteOrder[i]].y - g_cub.posY;

		//transform sprite with the inverse camera matrix
		// [ planeX   dirX ] -1                                       [ dirY      -dirX ]
		// [               ]       =  1/(planeX*dirY-dirX*planeY) *   [                 ]
		// [ planeY   dirY ]                                          [ -planeY  planeX ]

		double invDet = 1.0 / (g_cub.planeX * g_cub.dirY - g_cub.player.dirX * g_cub.planeY); //required for correct matrix multiplication

		double transformX = invDet * (g_cub.dirY * spriteX - g_cub.dirX * spriteY);
		double transformY = invDet * (-g_cub.planeY * spriteX + g_cub.planeX * spriteY); //this is actually the depth inside the screen, that what Z is in 3D, the distance of sprite to player, matching sqrt(spriteDistance[i])

		int spriteScreenX = (int)((width / 2) * (1 + transformX / transformY));

		//parameters for scaling and moving the sprites
		#define uDiv 1
		#define vDiv 1
		#define vMove 0.0
		int vMoveScreen = (int)(vMove / transformY);

		//calculate height of the sprite on screen
		int spriteHeight = (int)fabs((height / transformY) / vDiv); //using "transformY" instead of the real distance prevents fisheye
		//calculate lowest and highest pixel to fill in current stripe
		int drawStartY = -spriteHeight / 2 + height / 2 + vMoveScreen;
		if(drawStartY < 0) drawStartY = 0;
		int drawEndY = spriteHeight / 2 + height / 2 + vMoveScreen;
		if(drawEndY >= height) drawEndY = height - 1;

		//calculate width of the sprite
		int spriteWidth = (int)fabs((height / transformY) / uDiv);
		int drawStartX = -spriteWidth / 2 + spriteScreenX;
		if(drawStartX < 0) drawStartX = 0;
		int drawEndX = spriteWidth / 2 + spriteScreenX;
		if(drawEndX >= width) drawEndX = width - 1;

		//loop through every vertical stripe of the sprite on screen
		for(int stripe = drawStartX; stripe < drawEndX; stripe++)
		{
			int texX = (int)((256 * (stripe - (-spriteWidth / 2 + spriteScreenX)) * texWidth / spriteWidth) / 256);
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) ZBuffer, with perpendicular distance
			if(transformY > 0 && stripe > 0 && stripe < width && transformY < g_cub.zBuffer[stripe])
			for(int y = drawStartY; y < drawEndY; y++) //for every pixel of the current stripe
			{
				int d = (y-vMoveScreen) * 256 - height * 128 + spriteHeight * 128; //256 and 128 factors to avoid floats
				int texY = ((d * texHeight) / spriteHeight) / 256;
				int color = g_cub.texture[sprite[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
				if((color & 0x00FFFFFF) != 0) g_cub.window.buf[y][stripe] = color; //paint pixel if it isn't black, black is the invisible color
			}
		}
	}
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
	cub->player.rot_speed = 0.02;
	
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
