/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 16:32:51 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 20:00:50 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	move_player_front_back(char **map, t_player *player, double move_speed)
{
	if (map[(int)(player->pos_x + player->dir_x * move_speed)]
			[(int)(player->pos_y)] == '0')
		player->pos_x += player->dir_x * move_speed;
	if (map[(int)(player->pos_x)]
			[(int)(player->pos_y + player->dir_y * move_speed)] == '0')
		player->pos_y += player->dir_y * move_speed;
}

void	move_player_left_right(char **map, t_player *player, double move_speed)
{
	if (map[(int)(player->pos_x + player->dir_y * 2 * move_speed)]
			[(int)(player->pos_y)] == '0')
		player->pos_x += player->dir_y * move_speed;
	if (map[(int)(player->pos_x)]
			[(int)(player->pos_y + -player->dir_x * 2 * move_speed)] == '0')
		player->pos_y += -player->dir_x * move_speed;
}

void	rotate_player(t_player *player, double rotate_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = player->dir_x;
	player->dir_x =
		player->dir_x * cos(rotate_speed) - player->dir_y * sin(rotate_speed);
	player->dir_y =
		old_dir_x * sin(rotate_speed) + player->dir_y * cos(rotate_speed);
	old_plane_x = player->plane_x;
	player->plane_x =
		player->plane_x * cos(rotate_speed) -
		player->plane_y * sin(rotate_speed);
	player->plane_y =
		old_plane_x * sin(rotate_speed) +
		player->plane_y * cos(rotate_speed);
}

void	update_player_rotation(t_player *player, t_map *map)
{
	if (g_cub.control.keyboard[KEY_W])
		move_player_front_back(map->data, player, player->move_speed);
	if (g_cub.control.keyboard[KEY_S])
		move_player_front_back(map->data, player, -player->move_speed);
	if (g_cub.control.keyboard[KEY_D])
		move_player_left_right(map->data, player, player->move_speed);
	if (g_cub.control.keyboard[KEY_A])
		move_player_left_right(map->data, player, -player->move_speed);
	if (g_cub.control.keyboard[KEY_AR_R])
		rotate_player(player, -player->rot_speed);
	if (g_cub.control.keyboard[KEY_AR_L])
		rotate_player(player, player->rot_speed);
}
