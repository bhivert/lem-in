/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 10:23:58 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/20 15:08:16 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static size_t	getpossibility(t_lemin *e, size_t room)
{
	size_t	i;
	size_t	n;

	i = (size_t)-1;
	n = 0;
	while (++i < ft_size(e->rooms))
	{
		if (e->adj_mat[room][i])
			++n;
	}
	return (n);
}

static size_t	getnextid(t_lemin *e, t_container *w, size_t room)
{
	t_room	**last;

//	last = ft_at_index();
}

static void		getways_rec(t_lemin *e, t_container *w, size_t current_room)
{
	size_t		i;
	size_t		possibility;
	t_container	*begins;

	i = (size_t)-1;
	if (!(begins = ft_new_container(VECTOR, sizeof(t_container *))))
		badalloc(__FILE__, __LINE__);
	if (current_room == e->end->id)
		ft_push_back(e->ways, &w);
	else
	{
		possibility = getpossibility(e, current_room);
		while (++i < possibility)
		{

		}
		ft_push_back(w, &current_room);
		while (++i < ft_size(e->rooms))
		{
			if (i)
				;
			// << ===
		}
	}
	ft_delete_container(&begins);
}

void			getways(t_lemin *e)
{
	t_container	*w;

	if (!(w = ft_new_container(VECTOR, sizeof(size_t))))
		badalloc(__FILE__, __LINE__);
	getways_rec(e, w, e->start->id);
}
