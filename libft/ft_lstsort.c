/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <hyeonski@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 21:11:50 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/23 21:14:21 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsort(t_list **begin_list, int (*cmp)())
{
	int		swapped;
	t_list	*ptr;
	void	*tmp;

	if (!*begin_list)
		return ;
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ptr = *begin_list;
		while (ptr->next)
		{
			if (cmp(ptr->content, ptr->next->content) > 0)
			{
				swapped = 1;
				tmp = ptr->content;
				ptr->content = ptr->next->content;
				ptr->next->content = tmp;
			}
			ptr = ptr->next;
		}
	}
}