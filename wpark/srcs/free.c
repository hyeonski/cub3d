/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:18:57 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 19:14:34 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_conf(t_cub3d *cub3d)
{
	int i;

	i = 0;
	if (cub3d->conf)
	{
		if (cub3d->conf->tex)
		{
			i = -1;
			while (++i < 5)
			{
				if (cub3d->conf->tex->path[i])
					ft_strfree(&cub3d->conf->tex->path[i]);
				if (cub3d->conf->tex->img[i])
					mlx_destroy_image(cub3d->mlx, cub3d->conf->tex->img[i]);
			}
			free(cub3d->conf->tex);
			cub3d->conf->tex = 0;
		}
		free(cub3d->conf);
		cub3d->conf = 0;
	}
}

static void	free_player(t_cub3d *cub3d)
{
	if (cub3d->player)
	{
		if (cub3d->player->pos)
		{
			free(cub3d->player->pos);
			cub3d->player->pos = 0;
		}
		if (cub3d->player->dir)
		{
			free(cub3d->player->dir);
			cub3d->player->dir = 0;
		}
		if (cub3d->player->plane)
		{
			free(cub3d->player->plane);
			cub3d->player->plane = 0;
		}
		free(cub3d->player);
		cub3d->player = 0;
	}
}

static void	free_grid(t_cub3d *cub3d)
{
	int i;

	if (cub3d->grid)
	{
		i = -1;
		while (++i < cub3d->conf->grid_h)
		{
			free(cub3d->grid[i]);
			cub3d->grid[i] = 0;
		}
		free(cub3d->grid);
		cub3d->grid = 0;
	}
}

static void	free_ray(t_cub3d *cub3d)
{
	if (cub3d->ray)
	{
		if (cub3d->ray->dir)
		{
			free(cub3d->ray->dir);
			cub3d->ray->dir = 0;
		}
		free(cub3d->ray);
		cub3d->ray = 0;
	}
}

int			free_all(t_cub3d *cub3d, int ret)
{
	free_grid(cub3d);
	free_player(cub3d);
	free_ray(cub3d);
	free_conf(cub3d);
	if (cub3d->zbuff)
		free(cub3d->zbuff);
	sp_clear(&cub3d->sp);
	if (cub3d->img)
		mlx_destroy_image(cub3d->mlx, cub3d->img);
	if (cub3d->mlx && cub3d->win)
	{
		mlx_destroy_window(cub3d->mlx, cub3d->win);
		free(cub3d->mlx);
		cub3d->mlx = 0;
	}
	return (ret);
}
