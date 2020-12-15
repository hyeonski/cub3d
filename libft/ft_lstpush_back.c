/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 21:59:46 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/14 22:01:12 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush_back(t_list **begin_list, void *data)
{
	t_list	*elem;
	t_list	*last;

	elem = ft_create_elem(data);
	if (!*begin_list)
	{
		*begin_list = elem;
		return ;
	}
	last = ft_lstlast(*begin_list);
	last->next = elem;
}
