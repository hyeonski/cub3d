/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 12:22:17 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/27 15:41:31 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		read_file_to_buf(char *map_file_path, t_str_arr *conf)
{
	int		fd;
	int		ret;
	char	*temp;
	
	if (!is_valid_file_name(map_file_path))
		return (print_error("invalid file name"));
	else if ((fd = open(map_file_path, O_RDONLY)) == -1)
		return (print_error(strerror(errno)));
	temp = 0;
	conf->size = 0;
	while ((ret = get_next_line(fd, &temp)) != 0)
	{
		if (ret == -1)
			return (print_error("config file init error"));
		if (ft_list_strjoin(conf, temp) == 0)
			return (print_error(strerror(errno)));
		free(temp);
	}
	free(temp);
	close(fd);
	return (0);
}

int	init_sprite(t_list **begin_list, t_map *map)
{
	int			i;
	int			j;
	t_sprite	*sprite;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (is_contain(map->data[i][j], "2"))
			{
				sprite = malloc(sizeof(t_sprite));
				sprite->x = 0.5 + i;
				sprite->y = 0.5 + j;
				sprite->tex_num = 4;	
				ft_lstpush_back(begin_list, (void*)sprite);
			}
			j++;
		}
		i++;
	}
	return (1);
}

int		init_cub(t_str_arr *conf)
{
	int			i;
	
	i =	-1;
	while (i++ < conf->size && !is_contain(conf->elem[i][0], " 01"))
	{
		if (ft_strlen(conf->elem[i]) == 0)
			continue ;
		if (parse_value(conf->elem[i]) == 0)
			return (0);
	}
	check_map_size(conf, i);
	set_map(conf->elem, i);
	init_player(&g_cub.map, &g_cub.player);
	init_sprite(&g_cub.sprite, &g_cub.map);
	g_cub.zBuffer = malloc(sizeof(double) * g_cub.window.width);
	return (1);
}


int		set_cub(char *map_file_path)
{
	t_str_arr	conf;

	ft_bzero(&conf, sizeof(conf));
	if (read_file_to_buf(map_file_path, &conf) == -1)
	{	
		free_2d_arr(conf.elem, conf.size);
		return (0);
	}
	else if (!is_valid_cub(&conf))
	{
		print_error("invalid config file");
		free_2d_arr(conf.elem, conf.size);
		return (0);
	}
	else if (!init_cub(&conf))
	{
		free_2d_arr(conf.elem, conf.size);
		return (0);
	}
	free_2d_arr(conf.elem, conf.size);
	return (1);
} 
