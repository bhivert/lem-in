/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 10:23:58 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/24 10:08:24 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "getways.h"

static void		checkway_fct(size_t *context, size_t *content)
{
	if (context[0] == *content)
		context[1] = 1;
}

size_t			checkway(t_container *way, size_t room)
{
	size_t	context[2];

	context[0] = room;
	context[1] = 0;
	ft_iter(way, context, (void(*)(void *, void *))&checkway_fct);
	return (context[1]);
}

void			getways_rec(t_lemin *e, t_container *current_way, \
					size_t current_room)
{
	t_container	*begins;
	t_container	**b;
	size_t		possibility;

	b = NULL;
	possibility = (size_t)-1;
	ft_push_back(current_way, &current_room);
	if (current_room == e->end->id)
		ft_push_back(e->ways, &current_way);
	else
	{
		if (!(begins = create_begins(e, current_way, current_room)))
			badalloc(__FILE__, __LINE__);
		while (ft_size(begins))
		{
			if ((possibility = getnextpossibility(e, \
							current_room, possibility)) == (size_t)-1)
				break ;
			getways_rev_0(e, begins, b, possibility);
		}
		ft_set_content_destroy(begins, (void(*)(void *))&ft_delete_container);
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
