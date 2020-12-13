/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:53:12 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/13 17:09:01 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		set_player(t_player *player, int x, int y, char dir)
{
	player->posX = 0.5 + y;
	player->posY = 0.5 + x;
	if (dir == 'E')
	{
		player->dirY = 1;
		player->planeX = 0.66;
	}
	else if (dir == 'W')
	{
		player->dirY = -1;
		player->planeX = -0.66;
	}
	else if (dir == 'S')
	{
		player->dirX = 1;
		player->planeY = -0.66;
	}
	else
	{
		player->dirX = -1;
		player->planeY = 0.66;
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