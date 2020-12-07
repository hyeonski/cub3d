/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_shot.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:18:19 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 17:18:13 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_int_in_char(unsigned char *header, unsigned int value)
{
	unsigned int	*ptr;

	ptr = (unsigned int*)header;
	*ptr = value;
}

static int	write_bmp_header(int fd, int filesize, t_cub3d *cub3d)
{
	int				i;
	int				tmp;
	unsigned char	bmpfileheader[54];

	i = 0;
	while (i < 54)
		bmpfileheader[i++] = (unsigned char)(0);
	bmpfileheader[0] = (unsigned char)('B');
	bmpfileheader[1] = (unsigned char)('M');
	set_int_in_char(bmpfileheader + 2, filesize);
	bmpfileheader[10] = (unsigned char)(54);
	bmpfileheader[14] = (unsigned char)(40);
	tmp = cub3d->conf->res_w;
	set_int_in_char(bmpfileheader + 18, tmp);
	tmp = -cub3d->conf->res_h;
	set_int_in_char(bmpfileheader + 22, tmp);
	bmpfileheader[26] = (unsigned char)(1);
	bmpfileheader[28] = (unsigned char)(24);
	write(fd, bmpfileheader, 54);
	return (1);
}

static int	get_color(t_cub3d *cub3d, __uint32_t *data, int x, int y)
{
	int	rgb;
	int	color;

	color = data[cub3d->conf->res_w * y + x];
	rgb = (color & 0xFF0000) | (color & 0x00FF00) | (color & 0x0000FF);
	return (rgb);
}

static int	write_bmp_data(int file, t_cub3d *cub3d, unsigned int pad)
{
	const unsigned char	zero[3] = {0, 0, 0};
	int					i;
	int					j;
	int					color;

	i = 0;
	while (i < cub3d->conf->res_h)
	{
		j = 0;
		while (j < cub3d->conf->res_w)
		{
			color = get_color(cub3d, cub3d->data, j, i);
			if (write(file, &color, 3) < 0)
				return (0);
			j++;
		}
		if (pad > 0 && write(file, &zero, pad) < 0)
			return (0);
		i++;
	}
	return (1);
}

int			screen_shot(t_cub3d *cub3d)
{
	int				fd;
	unsigned int	pixel_bytes_per_row;
	unsigned int	padding_bytes_per_row;
	unsigned int	filesize;

	raycasting(cub3d);
	pixel_bytes_per_row = cub3d->conf->res_w * 3;
	padding_bytes_per_row = (4 - (pixel_bytes_per_row % 4)) % 4;
	filesize = 54
		+ (pixel_bytes_per_row
		+ padding_bytes_per_row) * cub3d->conf->res_h;
	if ((fd = open("screenshot.bmp", O_WRONLY | O_CREAT | O_TRUNC,
		S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)) < 0)
		return (0);
	if (!write_bmp_header(fd, filesize, cub3d))
		return (0);
	if (!write_bmp_data(fd, cub3d, padding_bytes_per_row))
		return (0);
	close(fd);
	free_all(cub3d, 0);
	return (1);
}
