/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 14:22:54 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 20:00:50 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void					set_int_in_char(unsigned char *start, int value)
{
	start[0] = (unsigned char)(value);
	start[1] = (unsigned char)(value >> 8);
	start[2] = (unsigned char)(value >> 16);
	start[3] = (unsigned char)(value >> 24);
}

void					write_bmp_header(int fd, int width, int height)
{
	unsigned char		header[54];

	ft_memset(header, 0, 54);
	header[0] = (unsigned char)'B';
	header[1] = (unsigned char)'M';
	set_int_in_char(header + 2, 54 + 3 * width * height);
	header[10] = (unsigned char)54;
	header[14] = (unsigned char)40;
	set_int_in_char(header + 18, width);
	set_int_in_char(header + 22, height);
	header[26] = (unsigned char)1;
	header[28] = (unsigned char)24;
	write(fd, header, 54);
}

void					write_data(int fd, int **buf, int width, int height)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					pad;

	i = height - 1;
	pad = (4 - (width * 3) % 4) % 4;
	while (i >= 0)
	{
		j = 0;
		while (j < width)
		{
			write(fd, &buf[i][j], 3);
			j++;
		}
		if (pad > 0)
			write(fd, &zero, pad);
		i--;
	}
}

int						save_image_to_bmp_file(int **buf, int width, int height)
{
	int					fd;

	if ((fd = open("screenshot.bmp",
					O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 00755)) < 0)
		return (print_error("Failed to save screenshot"));
	write_bmp_header(fd, width, height);
	write_data(fd, buf, width, height);
	close(fd);
	return (1);
}
