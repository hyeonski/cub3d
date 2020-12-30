/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:51:47 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/30 09:52:24 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

t_cub		g_cub;

int			exit_hook(int ret)
{
	exit(0);
	return (ret);
}

void		update_screen(t_cub *cub, t_window *window)
{
	update_img_from_buf(window, g_cub.data);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->imgptr, 0, 0);
}

int			main_loop(t_cub *cub)
{
	draw_floor_ceil(&cub->window, &cub->player);
	draw_wall(cub, &cub->window);
	draw_sprite(cub);
	update_screen(cub, &cub->window);
	update_player_rotation(&cub->player, &cub->map);
	return (0);
}

void		init_game(t_cub *cub)
{
	int		temp;

	cub->player.move_speed = 0.05;
	cub->player.rot_speed = 0.03;
	cub->win = mlx_new_window(cub->mlx,
			cub->window.width, cub->window.height, "cub3d");
	cub->imgptr =
		mlx_new_image(cub->mlx, cub->window.width, cub->window.height);
	cub->data = (int *)mlx_get_data_addr(cub->imgptr, &temp, &temp, &temp);
	mlx_loop_hook(cub->mlx, &main_loop, cub);
	mlx_hook(cub->win, X_EVENT_KEY_PRESS, 0, &key_press, &cub->control);
	mlx_hook(cub->win, X_EVENT_KEY_RELEASE, 0, &key_release, &cub->control);
	mlx_hook(cub->win, X_EVENT_KEY_EXIT, 0, exit_hook, 0);
	mlx_loop(cub->mlx);
}

int			main(int ac, char **av)
{
	g_cub.mlx = mlx_init();
	if (ac > 3 || ac == 1
		|| (ac == 3 && ft_strcmp("--save", av[2]) != 0))
		return (print_error("Invalid Argument"));
	if (!set_cub(av[1]))
		return (-1);
	if (ac == 3 && ft_strcmp("--save", av[2]) == 0)
	{
		draw_floor_ceil(&g_cub.window, &g_cub.player);
		draw_wall(&g_cub, &g_cub.window);
		draw_sprite(&g_cub);
		save_image_to_bmp_file(g_cub.window.buf,
						g_cub.window.width, g_cub.window.height);
		free_2d_arr((char **)g_cub.window.buf, g_cub.window.height);
		free_2d_arr(g_cub.map.data, g_cub.map.height);
		free_texture(g_cub.texture);
	}
	else
		init_game(&g_cub);
	return (0);
}
