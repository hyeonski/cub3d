/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_grid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:19:07 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 14:19:42 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	make_grid_line(char *line, char *new_line, int w)
{
	int	nb;
	int	ck;
	int	i;

	nb = 0;
	ck = 0;
	i = 0;
	while (i != w)
	{
		if (ck == 0 && ft_isdigit(*line) && (ck = 1))
			nb = nb * 10 + *line - '0';
		else if (ck == 0 && is_nsew(*line) && (ck = 1))
			nb = *line;
		else if (!ft_isdigit(*line) && !is_nsew(*line) && ck == 1)
		{
			new_line[i++] = nb;
			nb = 0;
			ck = 0;
		}
		line++;
	}
}

char		**join_grid(char **grid, char *line, t_cub3d *cub3d)
{
	char	**new_grid;
	char	*new_line;
	int		i;

	if (!(new_grid = (char**)malloc(sizeof(char*) * cub3d->conf->grid_h)))
	{
		cub3d->conf->grid_h -= 1;
		return (0);
	}
	if (!(new_line = (char*)malloc(sizeof(char) * cub3d->conf->grid_w)))
	{
		cub3d->conf->grid_h -= 1;
		return (0);
	}
	make_grid_line(line, new_line, cub3d->conf->grid_w);
	i = -1;
	while (++i < cub3d->conf->grid_h - 1)
		new_grid[i] = grid[i];
	new_grid[i] = new_line;
	return (new_grid);
}
