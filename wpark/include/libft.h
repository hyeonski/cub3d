/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 10:46:12 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 15:20:10 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# define BUFFER_SIZE 100
# include <stdlib.h>
# include <unistd.h>

int		ft_atoi(const char *str);
char	*ft_itoa(int n);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strsub(char const *s, unsigned int start, size_t len);
int		get_next_line(int fd, char **line);
void	ft_strfree(char **s);
int		ft_strlast(char const *str, char const *last);

#endif
