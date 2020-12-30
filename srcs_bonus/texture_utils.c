/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 09:50:09 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/30 10:09:09 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void			free_texture(t_texture *texture)
{
	int			i;

	i = 0;
	while (i < 7)
	{
		free(texture[i].data);
		i++;
	}
}

void			copy_img_data(int *dest, int *src, int width, int height)
{
	int			x;
	int			y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			dest[width * y + x] = src[width * y + x];
			x++;
		}
		y++;
	}
}
