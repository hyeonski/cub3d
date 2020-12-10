/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:34:02 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/10 17:35:23 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_list_strjoin(t_str_arr *str_arr, char *str)
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

	// for (int i = 0; i < str_arr->size; i++)
	// {
	// 	printf("%d: %s\n", i, str_arr->elem[i]);
	// }
	set_cub(&g_cub, str_arr);
	return (1);
}
