/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wpark <wpark@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:17:47 by wpark             #+#    #+#             */
/*   Updated: 2019/12/04 15:08:00 by wpark            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_sprite	*sp_new(int x, int y)
{
	t_sprite	*new;

	if (!(new = (t_sprite*)malloc(sizeof(t_sprite))))
		return (0);
	new->x = (double)x + 0.5;
	new->y = (double)y + 0.5;
	new->dist = 0.0;
	new->next = 0;
	return (new);
}

static void		sp_sort(t_sprite **begin)
{
	t_sprite	*sp;
	t_sprite	*bef;
	t_sprite	*nxt;

	if (*begin)
	{
		sp = *begin;
		bef = 0;
		while (sp->next)
		{
			nxt = sp->next;
			if (sp->dist < nxt->dist)
			{
				sp->next = nxt->next;
				nxt->next = sp;
				if (bef)
					bef->next = nxt;
				else
					*begin = nxt;
				sp = *begin;
			}
			bef = sp;
			sp = sp->next;
		}
	}
}

void			sp_add_back(t_sprite **begin, int x, int y)
{
	t_sprite	*sp;

	if (!*begin)
		*begin = sp_new(x, y);
	else
	{
		sp = *begin;
		while (sp->next)
			sp = sp->next;
		sp->next = sp_new(x, y);
	}
}

void			sp_clear(t_sprite **begin)
{
	t_sprite	*sp;
	t_sprite	*nxt;

	sp = *begin;
	while (sp)
	{
		nxt = sp->next;
		free(sp);
		sp = nxt;
	}
	*begin = 0;
}

void			sp_update_by_dist(t_sprite **begin, t_pos *p_pos)
{
	t_sprite	*sp;

	sp = *begin;
	while (sp)
	{
		sp->dist = (p_pos->x - sp->x) * (p_pos->x - sp->x)
			+ (p_pos->y - sp->y) * (p_pos->y - sp->y);
		sp = sp->next;
	}
	sp_sort(begin);
}
