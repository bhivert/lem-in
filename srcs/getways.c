/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 10:23:58 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/23 10:47:29 by bhivert          ###   ########.fr       */
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

t_container		*create_begins(t_lemin *e, t_container *current_way, \
					size_t current_room)
{
	size_t		i;
	size_t		possibility;
	t_container	*tmp;
	t_container	*begins;

	if (!(begins = ft_new_container(VECTOR, sizeof(t_container *))))
		badalloc(__FILE__, __LINE__);
	possibility = getpossibility(e, current_room);
	while (++i < possibility)
	{
		if (!(tmp = ft_copy(current_way)))
			badalloc(__FILE__, __LINE__);
		ft_push_back(begins, &tmp);
	}
	return (begins);
}

static size_t	getnextpossibility(t_lemin *e, t_container *current_room, \
					size_t possibility)
{
	return (-1);
}

static void		getways_rec(t_lemin *e, t_container *current_way, \
					size_t current_room)
{
	size_t		i;
	t_container	*begins;
	t_container	**b;

	i = (size_t)-1;
	if (current_room == e->end->id)
		ft_push_back(e->ways, &current_way);
	else
	{
		while (++i < ft_size(begins))
		{
			begins = create_begins(e, current_way, current_room);
			if ((b = ft_at_index(begins, 0)))
			{
				;
			}
		}
		// push possibility

		ft_delete_container(&begins);
	}
}

void			getways(t_lemin *e)
{
	t_container	*w;

	if (!(w = ft_new_container(VECTOR, sizeof(size_t))))
		badalloc(__FILE__, __LINE__);
	getways_rec(e, w, e->start->id);
}
