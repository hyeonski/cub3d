/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 17:21:07 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/28 17:47:47 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int			is_map_arg(int c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W'
	|| c == ' ' || (c >= '0' && c <= '2') || c == '\n'
	|| c == '\0')
		return (1);
	return (0);
}

int			get_next_dir_x(int x, int dir)
{
	if (dir == 0)
		return (x + 1);
	if (dir == 1)
		return (x - 1);
	if (dir == 2)
		return (x);
	else
		return (x);
}

int			get_next_dir_y(int y, int dir)
{
	if (dir == 0)
		return (y);
	if (dir == 1)
		return (y);
	if (dir == 2)
		return (y + 1);
	else
		return (y - 1);
}
