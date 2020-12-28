/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:08:24 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/28 18:30:49 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		compare_sprite_dist(t_sprite *lhs, t_sprite *rhs)
{
	int	lhs_dist;
	int	rhs_dist;

	lhs_dist =
		(lhs->x - g_cub.player.pos_x) *
		(lhs->x - g_cub.player.pos_x) +
		(lhs->y - g_cub.player.pos_y) *
		(lhs->y - g_cub.player.pos_y);
	rhs_dist =
		(rhs->x - g_cub.player.pos_x) *
		(rhs->x - g_cub.player.pos_x) +
		(rhs->y - g_cub.player.pos_y) *
		(rhs->y - g_cub.player.pos_y);
	return (lhs_dist < rhs_dist);
}
