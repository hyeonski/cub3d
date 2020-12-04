/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 09:56:27 by hyeonski          #+#    #+#             */
/*   Updated: 2020/10/16 23:43:21 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	read_file(int fd, char **strd, char *buf, char **nl)
{
	int		read_size;
	char	*temp;

	read_size = 1;
	while (((*nl) = ft_strchr(strd[fd], '\n')) == 0 && read_size != 0)
	{
		if ((read_size = read(fd, buf, BUFFER_SIZE)) == -1)
		{
			free(buf);
			return (-1);
		}
		buf[read_size] = '\0';
		temp = strd[fd] == NULL ? ft_strdup(buf) : ft_strjoin(strd[fd], buf);
		if (strd[fd])
			free(strd[fd]);
		strd[fd] = temp;
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static char	*stored[OPEN_MAX];
	int			read_size;
	char		*nl;
	char		*buf;
	char		*temp;

	read_size = 1;
	nl = 0;
	if (fd < 0 || BUFFER_SIZE <= 0 || !line || fd > OPEN_MAX)
		return (-1);
	if (!(buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))) ||
					read_file(fd, stored, buf, &nl) == -1)
		return (-1);
	if (nl != NULL && (temp = stored[fd]))
	{
		*line = ft_substr(stored[fd], 0, nl - stored[fd]);
		stored[fd] = ft_strdup(nl + 1);
		free(temp);
		free(buf);
		return (1);
	}
	*line = stored[fd];
	stored[fd] = NULL;
	free(buf);
	return (0);
}
