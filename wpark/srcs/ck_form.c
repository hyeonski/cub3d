/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ck_form.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:19:11 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 17:23:09 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ck_grid_form(char *form)
{
	int grid_w;
	int	ck;

	grid_w = 0;
	ck = 0;
	while (*form != '\0')
	{
		if (*form != '0' && *form != '1' && *form != '2' && *form != ' '
			&& *form != 'N' && *form != 'S' && *form != 'E' && *form != 'W')
			return (0);
		if (ck == 0 && (ft_isdigit(*form) || *form == 'N'
			|| *form == 'S' || *form == 'E' || *form == 'W') && (ck = 1))
			grid_w++;
		else if (ck == 1 && *form == ' ')
			ck = 0;
		form++;
	}
	return (grid_w);
}

int	ck_color_form(char *form)
{
	int	nb_num;
	int	ck;
	int res;

	res = 0;
	ck = 0;
	nb_num = 0;
	while (*form != '\0')
	{
		if (!ft_isdigit(*form) && *form != ' ' && *form != ',')
			return (0);
		if (ck == 0 && ft_isdigit(*form) && (ck = 1) && ++nb_num)
			res++;
		else if (ck == 1 && *form == ' ')
			ck = 0;
		else if (*form == ',' && !(ck = 0))
			res--;
		if (res != 1 && res != 0)
			return (0);
		form++;
	}
	if (nb_num != 3)
		return (0);
	return (1);
}

int	ck_resolution_form(char *form)
{
	int	ck;
	int	nb_num;

	ck = 0;
	nb_num = 0;
	while (*form != '\0')
	{
		if (!ft_isdigit(*form) && *form != ' ')
			return (0);
		if (ck == 1 && *form == ' ')
			ck = 0;
		if (ck == 0 && ft_isdigit(*form) && (ck = 1))
		{
			if (++nb_num > 2)
				return (0);
		}
		form++;
	}
	if (nb_num != 2)
		return (0);
	return (1);
}

int	is_wall(int new_x, int new_y, t_cub3d *cub3d)
{
	if (new_x > cub3d->conf->grid_w - 1 || new_y > cub3d->conf->grid_h - 1)
		return (1);
	if (cub3d->grid[new_y][new_x] == 1)
		return (1);
	if (cub3d->grid[new_y][new_x] == 2)
		return (2);
	return (0);
}

int	is_nsew(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}
