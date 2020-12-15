/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:53:12 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/13 20:58:12 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		set_player(t_player *player, int x, int y, char dir)
{
	player->pos_x = 0.5 + y;
	player->pos_y = 0.5 + x;
	if (dir == 'E')
	{
		player->dir_y = 1;
		player->plane_x = 0.66;
	}
	else if (dir == 'W')
	{
		player->dir_y = -1;
		player->plane_x = -0.66;
	}
	else if (dir == 'S')
	{
		player->dir_x = 1;
		player->plane_y = -0.66;
	}
	else
	{
		player->dir_x = -1;
		player->plane_y = 0.66;
	}
}

void	init_player(t_map *map, t_player *player)
{
	int			i;
	int			j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_contain(map->data[i][j], "EWSN"))
			{
				set_player(player, j, i, map->data[i][j]);
				map->data[i][j] = '0';
				return ;
			}
			j++;
		}
		i++;
	}
}