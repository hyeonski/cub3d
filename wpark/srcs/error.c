/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:18:59 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 19:16:15 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	err_msg(int erno, char *msg, int ret)
{
	write(STDERR_FILENO, "Error:\n", 7);
	if (erno < 0)
		ft_putstr_fd(msg, STDERR_FILENO);
	else
		strerror(errno);
	return (ret);
}

int			err_free(int erno, char *msg, t_cub3d *cub3d, int ret)
{
	err_msg(erno, msg, ret);
	return (free_all(cub3d, ret));
}
