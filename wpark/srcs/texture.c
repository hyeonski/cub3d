/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:17:41 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 15:11:01 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_texture_img(t_cub3d *cub3d, t_tex *tex)
{
	if (!(tex->img[TEX_N] = mlx_xpm_file_to_image(cub3d->mlx,
		tex->path[TEX_N], &tex->wh[TEX_N][0], &tex->wh[TEX_N][1])))
		return (err_free(-1, "Failed to load North texture.\n", cub3d, 0));
	if (!(tex->img[TEX_S] = mlx_xpm_file_to_image(cub3d->mlx,
		tex->path[TEX_S], &tex->wh[TEX_S][0], &tex->wh[TEX_S][1])))
		return (err_free(-1, "Failed to load South texture.\n", cub3d, 0));
	if (!(tex->img[TEX_W] = mlx_xpm_file_to_image(cub3d->mlx,
		tex->path[TEX_W], &tex->wh[TEX_W][0], &tex->wh[TEX_W][1])))
		return (err_free(-1, "Failed to load West texture.\n", cub3d, 0));
	if (!(tex->img[TEX_E] = mlx_xpm_file_to_image(cub3d->mlx,
		tex->path[TEX_E], &tex->wh[TEX_E][0], &tex->wh[TEX_E][1])))
		return (err_free(-1, "Failed to load East texture.\n", cub3d, 0));
	if (!(tex->img[TEX_O] = mlx_xpm_file_to_image(cub3d->mlx,
		tex->path[TEX_O], &tex->wh[TEX_O][0], &tex->wh[TEX_O][1])))
		return (err_free(-1, "Failed to load Sprite texture.\n", cub3d, 0));
	return (1);
}

static int	set_texture_data(t_cub3d *cub3d, t_tex *tex)
{
	if (!(tex->data[TEX_N] = mlx_get_data_addr(tex->img[TEX_N],
		&tex->bpp, &tex->size_line, &tex->endian)))
		return (err_free(-1, "Failed to get North texture data.\n", cub3d, 0));
	if (!(tex->data[TEX_S] = mlx_get_data_addr(tex->img[TEX_S],
		&tex->bpp, &tex->size_line, &tex->endian)))
		return (err_free(-1, "Failed to get South texture data.\n", cub3d, 0));
	if (!(tex->data[TEX_E] = mlx_get_data_addr(tex->img[TEX_E],
		&tex->bpp, &tex->size_line, &tex->endian)))
		return (err_free(-1, "Failed to get East texture data.\n", cub3d, 0));
	if (!(tex->data[TEX_W] = mlx_get_data_addr(tex->img[TEX_W],
		&tex->bpp, &tex->size_line, &tex->endian)))
		return (err_free(-1, "Failed to get West texture data.\n", cub3d, 0));
	if (!(tex->data[TEX_O] = mlx_get_data_addr(tex->img[TEX_O],
		&tex->bpp, &tex->size_line, &tex->endian)))
		return (err_free(-1, "Failed to get Sprite texture data.\n", cub3d, 0));
	return (1);
}

int			load_texture(t_cub3d *cub3d)
{
	t_tex		*tex;

	tex = cub3d->conf->tex;
	if (!set_texture_img(cub3d, tex))
		return (0);
	if (!set_texture_data(cub3d, tex))
		return (0);
	return (1);
}
