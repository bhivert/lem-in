/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 10:23:58 by bhivert           #+#    #+#             */
/*   Updated: 2016/06/06 09:15:56 by bhivert          ###   ########.fr       */
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

	i = (size_t)-1;
	if (!(begins = ft_new_container(VECTOR, sizeof(t_container *))))
		badalloc(__FILE__, __LINE__);
	possibility = getpossibility(e, current_room);
	ft_push_back(begins, &current_way);
	while (++i < possibility - 1)
	{
		if (!(tmp = ft_copy(current_way)))
			badalloc(__FILE__, __LINE__);
		ft_push_back(begins, &tmp);
	}
	return (begins);
}

static size_t	getnextpossibility(t_lemin *e, size_t current_room, \
					size_t last_possibility)
{
	size_t	i;

	i = last_possibility;
	while (++i < ft_size(e->rooms))
	{
		if (e->adj_mat[current_room][i])
			return (i);
	}
	return (-1);
}

void		checkway_fct(size_t *context, size_t *content)
{
	if (context[0] == *content)
		context[1] = 1;
}

static int		checkway(t_container *way, size_t room)
{
	size_t	context[2];

	context[0] = room;
	context[1] = 0;
	ft_iter(way, context, (void(*)(void *, void *))&checkway_fct);
	return (context[1]);
}

static void		getways_rec(t_lemin *e, t_container *current_way, \
					size_t current_room)
{
	t_container	*begins;
	t_container	**b;
	size_t		possibility;

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
			if ((possibility = getnextpossibility(e, current_room, possibility)) == (size_t)-1)
				break ;
			if ((b = ft_at_index(begins, ft_size(begins) - 1)))
			{
				if (!checkway(*b, possibility))
					getways_rec(e, *b, possibility);
				else
					ft_delete_container(b);
				ft_pop_back(begins);
			}
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
