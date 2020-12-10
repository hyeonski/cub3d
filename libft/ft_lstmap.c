/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyeonski <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 17:06:01 by hyeonski          #+#    #+#             */
/*   Updated: 2020/10/07 21:07:49 by hyeonski         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*temp;
	t_list	*curr;

	if (lst == 0 || f == 0 || (result = ft_lstnew(f(lst->content))) == 0)
		return (0);
	curr = result;
	temp = lst->next;
	while (temp)
	{
		if (!(curr->next = ft_lstnew(f(temp->content))))
		{
			ft_lstclear(&result, del);
			return (0);
		}
		curr = curr->next;
		temp = temp->next;
	}
	return (result);
}
