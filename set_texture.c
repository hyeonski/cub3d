/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 16:53:32 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/10 16:55:16 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_window	init_window(int width, int height)
{
	t_window	window;
	int			i;

	if (width * 3 != height * 4)
		height = (double)width * 3 / 4;
	window.width = width;
	window.height = height;
	window.buf = (int**)malloc(window.height * sizeof(int*));
	i = -1;
	while (++i < window.height)
		window.buf[i] = (int*)malloc(window.width * sizeof(int));
	return (window);
}

t_rgb	init_rgb(char *s)
{
	t_rgb	rgb;
	char	**token;

	token = ft_split(s, ',');
	rgb.r = ft_atoi(token[0]);
	rgb.g = ft_atoi(token[1]);
	rgb.b = ft_atoi(token[2]);
	free_2d_arr(token, 3);
	return (rgb);
}


int	load_texture(t_texture *texture, char *file_path)
{
	int		tmp;
	void	*img;

	img = mlx_xpm_file_to_image(g_cub.mlx, file_path, &texture->width, &texture->height);
	if (!img)
		return (0);
	texture->data = (int *)mlx_get_data_addr(img, &tmp, &tmp, &tmp);
	return (texture->data != 0);
}

int		parse_key_texture(t_cub *cub, char *key, char *file_path)
{
	int ret;

	if (ft_strcmp(key, "EA") == 0)
		ret = load_texture(&cub->texture[0], file_path);
	else if (ft_strcmp(key, "WE") == 0)
		ret = load_texture(&cub->texture[1], file_path);
	else if (ft_strcmp(key, "SO") == 0)
		ret = load_texture(&cub->texture[2], file_path);
	else if (ft_strcmp(key, "NO") == 0)
		ret = load_texture(&cub->texture[3], file_path);
	else
		ret = load_texture(&cub->texture[4], file_path);
	return (ret);
}

int		parse_key(t_cub *cub, char *s)
{
	char	**token;
	int		cnt;
	int		len;

	token = ft_split(s, ' ');
	len = (int)ft_strlen(token[0]);
	if (len == 1 && is_included(token[0][0], "RFC"))
	{
		if (token[0][0] == 'R')
			cub->window = init_window(ft_atoi(token[1]), ft_atoi(token[2]));
		else if (token[0][0] == 'F')
			cub->floor = init_rgb(token[1]);
		else
			cub->ceil = init_rgb(token[1]);
	}
	else
		parse_key_texture(cub, token[0], token[1]);
	return (1);
}