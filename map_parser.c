/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:34:02 by hyeonski          #+#    #+#             */
/*   Updated: 2020/11/28 16:49:38 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>

int		map_parser(char *map)
{
	int		fd;
	char	*temp;

	fd = open(map, O_RDONLY);
	temp = 0;
	while (get_next_line(fd, &temp) > 0)
	{
		
	}
}

int main(int ac, char **av)
{
	map_parser(av[1]);
	return (0);
}