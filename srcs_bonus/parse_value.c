/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:38:22 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 20:07:32 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

int				load_texture(t_texture *texture, char *file_path)
{
	int			tmp;
	void		*imgptr;

	imgptr = mlx_xpm_file_to_image(g_cub.mlx, file_path,
			&texture->width, &texture->height);
	if (!imgptr)
		return (0);
	texture->data = (int *)mlx_get_data_addr(imgptr, &tmp, &tmp, &tmp);
	return (texture->data != 0);
}

int				set_texture(char *key, char *file_path)
{
	int			ret;

	if (ft_strcmp(key, "EA") == 0)
		ret = load_texture(&g_cub.texture[0], file_path);
	else if (ft_strcmp(key, "WE") == 0)
		ret = load_texture(&g_cub.texture[1], file_path);
	else if (ft_strcmp(key, "SO") == 0)
		ret = load_texture(&g_cub.texture[2], file_path);
	else if (ft_strcmp(key, "NO") == 0)
		ret = load_texture(&g_cub.texture[3], file_path);
	else
		ret = load_texture(&g_cub.texture[4], file_path);
	if (!ret)
		print_error("texture loading failed");
	return (ret);
}

void			set_window(int width, int height)
{
	t_window	window;
	int			i;

	width = (width > 1000 ? 1000 : width);
	width = (width < 100 ? 100 : width);
	if (width * 3 != height * 4)
		height = (double)width * 3 / 4;
	window.width = width;
	window.height = height;
	window.buf = (int **)malloc(window.height * sizeof(int *));
	i = 0;
	while (i < window.height)
		window.buf[i++] = (int *)malloc(window.width * sizeof(int));
	g_cub.window = window;
}

t_rgb			set_rgbcolor(char *value)
{
	t_rgb		color;
	char		**res;

	res = ft_split(value, ',');
	color.r = ft_atoi(res[0]);
	color.g = ft_atoi(res[1]);
	color.b = ft_atoi(res[2]);
	free_2d_arr(res, 3);
	return (color);
}

int				parse_value(char *key)
{
	char		**res;
	int			size;

	res = ft_split(key, ' ');
	size = ft_2d_arr_size(res);
	if (ft_strlen(res[0]) == 1 && is_contain(res[0][0], "RFC"))
	{
		if (res[0][0] == 'R')
			set_window(ft_atoi(res[1]), ft_atoi(res[2]));
		else if (res[0][0] == 'F')
			g_cub.floor = set_rgbcolor(res[1]);
		else
			g_cub.ceiling = set_rgbcolor(res[1]);
	}
	else if (!set_texture(res[0], res[1]))
		return (0);
	free_2d_arr(res, size);
	return (1);
}
