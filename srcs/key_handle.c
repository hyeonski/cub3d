/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:42:57 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/28 15:19:41 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		key_press(int key, t_control *control)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W)
		control->keyboard[KEY_W] = 1;
	else if (key == KEY_A)
		control->keyboard[KEY_A] = 1;
	else if (key == KEY_S)
		control->keyboard[KEY_S] = 1;
	else if (key == KEY_D)
		control->keyboard[KEY_D] = 1;
	else if (key == KEY_AR_L)
		control->keyboard[KEY_AR_L] = 1;
	else if (key == KEY_AR_R)
		control->keyboard[KEY_AR_R] = 1;
	return (0);
}

int		key_release(int key, t_control *control)
{
	if (key == KEY_ESC)
		exit(0);
	else if (key == KEY_W)
		control->keyboard[KEY_W] = 0;
	else if (key == KEY_A)
		control->keyboard[KEY_A] = 0;
	else if (key == KEY_S)
		control->keyboard[KEY_S] = 0;
	else if (key == KEY_D)
		control->keyboard[KEY_D] = 0;
	else if (key == KEY_AR_L)
		control->keyboard[KEY_AR_L] = 0;
	else if (key == KEY_AR_R)
		control->keyboard[KEY_AR_R] = 0;
	return (0);
}
