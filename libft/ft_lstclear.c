/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 16:57:32 by hyeonski          #+#    #+#             */
/*   Updated: 2020/12/29 21:39:02 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*temp;
	t_list	*curr;

	curr = *lst;
	while (curr)
	{
		temp = curr->next;
		del(curr->content);
		free(curr);
		curr = temp;
	}
	*lst = NULL;
}
