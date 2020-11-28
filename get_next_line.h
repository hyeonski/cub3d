/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 09:57:15 by hyeonski          #+#    #+#             */
/*   Updated: 2020/10/15 19:22:42 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4095

# endif
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

int		ft_strlen(const char *s);
char	*ft_strchr(char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char *str, unsigned int start, int len);
char	*ft_strdup(char *str);
int		get_next_line(int fd, char **line);

#endif
