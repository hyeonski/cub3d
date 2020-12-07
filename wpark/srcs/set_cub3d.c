/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cub3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:18:05 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 17:49:55 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** check if map is surounded by 1
** check if there is only on "N/S/E/W"
** check if there is charactor except from 0, 1, 2, NSEW
*/

static int	ck_extention(char *map_file, t_cub3d *cub3d)
{
	if (!ft_strlast(map_file, ".cub"))
	{
		return (err_free(-1,
			"Invalide map file. Please check file extention(.cub)\n",
			cub3d, 0));
	}
	return (1);
}

static int	ck_config(t_cub3d *cub3d)
{
	t_config	*conf;

	conf = cub3d->conf;
	if (conf->res_w <= 0 || conf->res_h <= 0)
		return (err_free(-1, "Invlaide resolution number.\n", cub3d, 0));
	if (conf->res_w < RMIN_W || conf->res_h < RMIN_H)
	{
		conf->res_w = RMIN_W;
		conf->res_h = RMIN_H;
	}
	if (conf->color_c < 0)
		return (err_free(-1, "Ceiling color not defined.\n", cub3d, 0));
	if (conf->color_f < 0)
		return (err_free(-1, "Floor color not defined.\n", cub3d, 0));
	if (!(cub3d->zbuff = malloc(sizeof(double) * conf->res_w)))
		return (err_free(-1, "Failed to malloc zbuff.\n", cub3d, 0));
	if (!check_grid(cub3d))
		return (0);
	return (1);
}

int			set_cub3d(char *map_file, t_cub3d *cub3d)
{
	char	*line;
	int		fd;

	if (!ck_extention(map_file, cub3d))
		return (0);
	if ((fd = open(map_file, O_RDONLY)) < 0)
		return (err_free(errno, 0, cub3d, 0));
	line = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if (*line == '\0')
			ft_strfree(&line);
		else if (!get_config(line, cub3d) && get_next_line(-1, 0))
		{
			ft_strfree(&line);
			return (0);
		}
		else
			ft_strfree(&line);
	}
	ft_strfree(&line);
	close(fd);
	return (ck_config(cub3d));
}
