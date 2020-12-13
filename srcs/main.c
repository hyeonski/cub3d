/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:51:47 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/13 14:53:50 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_cub	g_cub;

int main(int ac, char **av)
{
	g_cub.mlx = mlx_init();
	// if (argc > 3 || argc == 1
	// 	|| (argc == 3 && ft_strcmp("--save", argv[2]) != 0))
	// 	return (print_error(cuberror(invalid_argument)));
	if (!init_game(av[1]))
		return (-1);
	// if (argc == 3)
	// {
	// 	update_scene();
	// 	save_image_to_bmp_file(g_cub.window.scene, g_cub.window.width,
	// 							g_cub.window.height);
	// }
	// else
	// 	init_mlx();
	
	return (0);
}