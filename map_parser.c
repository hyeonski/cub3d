/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:34:02 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/10 11:47:11 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_list_strjoin(t_str_arr *str_arr, char *str)
{
	char	**temp_elem;
	int		i;

	if (!(temp_elem = (char **)malloc(sizeof(char *) * (str_arr->size + 1))))
		return ;
	i = 0;
	while (i < str_arr->size)
	{
		temp_elem[i] = str_arr->elem[i];
		++i;
	}
	temp_elem[i] = ft_strjoin(str, "");
	free(str_arr->elem);
	str_arr->size += 1;
	str_arr->elem = temp_elem;
}


void	free_2d_arr(char **arr, int size)
{
	int i;

	i = 0;
	while (i < size)
		free(arr[i++]);
	free(arr);
}


int		is_included(char c, char *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
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

t_window	init_window(int width, int height)
{
	t_window	window;
	int			i;

	if (width * 3 != height * 4)
		height = (double)width * 3 / 4;
	window.width = width;
	window.height = height;
	window.scene = (int**)malloc(window.height * sizeof(int*));
	i = -1;
	while (++i < window.height)
		window.scene[i] = (int*)malloc(window.width * sizeof(int));
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

char	**init_chars_array(int row, int col, char c)
{
	char	**ret;
	int		i;

	ret = (char**)malloc(sizeof(char*) * row);
	i = 0;
	while (i < row)
	{
		ret[i] = (char*)malloc(sizeof(char) * col);
		ft_memset(ret[i], c, col);
		++i;
	}
	return (ret);
}


char		**init_map(char **strs, int start, t_map *map)
{
	char	**data;
	int		i;
	int		j;

	data = init_chars_array(map->height, map->width, ' ');
	i = 0;
	j = 0;
	while (i < map->height)
	{
		j = (int)ft_strlen(strs[start + i]);
		while (--j >= 0)
			data[i][j] = strs[start + i][j];
		++i;
	}
	return (data);
}

void	calc_size(t_str_arr *arr, int i, t_map *map)
{
	int			ret_width;
	int			ret_height;
	int			len;

	ft_memset(&ret_width, 0, sizeof(int));
	ft_memset(&ret_height, 0, sizeof(int));
	while (i < arr->size &&
			(len = (int)ft_strlen(arr->elem[i])) &&
			is_included(arr->elem[i][0], " 01"))
	{
		++ret_height;
		ret_width = ft_max(ret_width, len);
		++i;
	}
	map->width = ret_width;
	map->height = ret_height;
}

void		set_player(t_player *player, int x, int y, char dir)
{
	player->posX = 0.5 + y;
	player->posY = 0.5 + x;
	if (dir == 'E')
	{
		player->dirY = 1;
		player->planeX = 0.66;
	}
	else if (dir == 'W')
	{
		player->dirY = -1;
		player->planeX = -0.66;
	}
	else if (dir == 'S')
	{
		player->dirX = 1;
		player->planeY = -0.66;
	}
	else
	{
		player->dirX = -1;
		player->planeY = 0.66;
	}
}

t_player	init_player(t_map *map)
{
	t_player	p;
	int			i;
	int			j;

	ft_bzero(&p, sizeof(p));
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
			if (is_included(map->data[i][j], "EWSN"))
			{
				set_player(&p, j, i, map->data[i][j]);
				map->data[i][j] = '0';
				return (p);
			}
	}
	return (p);
}


int		set_cub(t_cub *cub, t_str_arr *conf)
{
	int i;

	ft_bzero(cub, sizeof(t_cub));
	i = -1;
	while (++i < conf->size && !is_included(conf->elem[i][0], " 01"))
	{
		if (ft_strlen(conf->elem[i]) == 0)
			continue;
		parse_key(cub, conf->elem[i]);
	}
	calc_size(conf, i, &cub->map);
	cub->map.data = init_map(conf->elem, i, &cub->map);
	cub->player = init_player(&cub->map);
	return (1);
}

int		map_parser(char *map, t_str_arr *str_arr)
{
	int		fd;
	char	*temp;

	fd = open(map, O_RDONLY);
	temp = 0;
	str_arr->size = 0;
	while (get_next_line(fd, &temp) > 0)
	{
		ft_list_strjoin(str_arr, temp);
		free(temp);
	}
	free(temp);
	close(fd);

	for (int i = 0; i < str_arr->size; i++)
	{
		printf("%d: %s\n", i, str_arr->elem[i]);
	}
	set_cub(&g_cub, str_arr);
	return (1);
}
