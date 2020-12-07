/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 20:59:46 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 16:43:59 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	config_color(char *line, t_cub3d *cub3d, char op)
{
	t_config	*conf;
	int			*color;
	int			nb;

	if (!ck_color_form(line))
		return (err_free(-1, "Inalide color format.\n", cub3d, 0));
	conf = cub3d->conf;
	color = (op == 'F') ? &(conf->color_f) : &(conf->color_c);
	nb = ft_atoi(line);
	if (nb < 0 || nb > 255)
		return (err_free(-1, "Inalide color format.\n", cub3d, 0));
	*color = nb << 16;
	while (*line != ',')
		line++;
	nb = ft_atoi(++line);
	if (nb < 0 || nb > 255)
		return (err_free(-1, "Inalide color format.\n", cub3d, 0));
	*color = *color + (nb << 8);
	while (*line != ',')
		line++;
	nb = ft_atoi(++line);
	if (nb < 0 || nb > 255)
		return (err_free(-1, "Inalide color format.\n", cub3d, 0));
	*color = *color + nb;
	return (1);
}

static int	config_texfile(char *line, t_cub3d *cub3d, char op)
{
	t_tex	*tex;

	tex = cub3d->conf->tex;
	while (*line == ' ')
		line++;
	if (op == 'N' && !(tex->path[TEX_N] = ft_strdup(line)))
		return (err_free(-1, "Failed to texfile malloc\n", cub3d, 0));
	else if (op == 'S' && !(tex->path[TEX_S] = ft_strdup(line)))
		return (err_free(-1, "Failed to texfile malloc\n", cub3d, 0));
	else if (op == 'W' && !(tex->path[TEX_W] = ft_strdup(line)))
		return (err_free(-1, "Failed to texfile malloc\n", cub3d, 0));
	else if (op == 'E' && !(tex->path[TEX_E] = ft_strdup(line)))
		return (err_free(-1, "Failed to texfile malloc\n", cub3d, 0));
	else if (op == 'O' && !(tex->path[TEX_O] = ft_strdup(line)))
		return (err_free(-1, "Failed to texfile malloc\n", cub3d, 0));
	return (1);
}

static int	config_resolution(char *line, t_cub3d *cub3d)
{
	t_config	*conf;
	int			nb;

	if (!ck_resolution_form(line))
		return (err_free(-1, "Invalide resolution format.\n", cub3d, 0));
	conf = cub3d->conf;
	while (*line == ' ')
		line++;
	nb = ft_atoi(line);
	if ((conf->res_w = nb) >= RMAX_W)
		conf->res_w = RMAX_W;
	while (ft_isdigit(*line))
		line++;
	nb = ft_atoi(line);
	if ((conf->res_h = nb) >= RMAX_H)
		conf->res_h = RMAX_H;
	return (1);
}

static int	config_grid(char *line, t_cub3d *cub3d, t_config *conf)
{
	int		grid_w;
	char	**new_grid;

	if (!(grid_w = ck_grid_form(line)))
	{
		return (err_free(-1,
			"Wrong map description : invlaide charactor.\n", cub3d, 0));
	}
	if (conf->grid_w != 0 && conf->grid_w != grid_w)
	{
		return (err_free(-1,
			"Wrong map description : invalide width.\n", cub3d, 0));
	}
	conf->grid_w = grid_w;
	conf->grid_h = conf->grid_h + 1;
	if (!(new_grid = join_grid(cub3d->grid, line, cub3d)))
		return (err_free(-1, "Grid malloc failed.\n", cub3d, 0));
	if (cub3d->grid)
		free(cub3d->grid);
	cub3d->grid = new_grid;
	return (1);
}

int			get_config(char *line, t_cub3d *cub3d)
{
	while (*line == ' ')
		line++;
	if (*line == 'F' || *line == 'C')
		return (config_color(line + 1, cub3d, *line));
	else if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2))
		return (config_texfile(line + 2, cub3d, *line));
	else if (*line == 'S')
		return (config_texfile(line + 1, cub3d, 'O'));
	else if (*line == 'R')
		return (config_resolution(line + 1, cub3d));
	else if (ft_isdigit(*line) && !config_grid(line, cub3d, cub3d->conf))
		return (0);
	else if (!ft_isdigit(*line))
	{
		return (err_free(-1,
			"Wrong map description : invalide charactor.\n", cub3d, 0));
	}
	return (1);
}
