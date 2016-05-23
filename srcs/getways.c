/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 10:23:58 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/23 15:33:12 by bhivert          ###   ########.fr       */
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

#include <stdio.h>

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
	while (++i < possibility)
	{
	write(1, "011\n", 4);
		if (!(tmp = ft_copy(current_way)))
			badalloc(__FILE__, __LINE__);
	write(1, "022\n", 4);
	printf("%p\n", tmp);
		ft_push_back(begins, &tmp);
	}
	printf("%p - %zu\n", begins, ft_size(begins));
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

static void		checkway_fct(size_t *rsl, size_t *content)
{
	if (*content == rsl[0] || *content == rsl[1])
		rsl[2] = 1;
}

static int		checkway(t_container *way, size_t start, size_t room)
{
	size_t		rsl[3];

	rsl[0] = start;
	rsl[1] = room;
	rsl[2] = 0;
	ft_iter(way, &rsl, (void(*)(void *, void *))&checkway_fct);
	return (rsl[2]);
}


static void		getways_rec(t_lemin *e, t_container *current_way, \
					size_t current_room)
{
	size_t		i;
	t_container	*begins;
	t_container	**b;
	size_t		possibility;

	i = (size_t)-1;
	possibility = (size_t)-1;
	if (current_room == e->end->id)
	{
	write(1, "222\n", 4);
		ft_push_back(e->ways, &current_way);
	}
	else
	{
		if ((begins = create_begins(e, current_way, current_room)))
		{
	printf("%p - %zu\n", begins, ft_size(begins));
			while (++i < ft_size(begins))
			{
				if ((b = ft_at_index(begins, ft_size(begins) - 1)))
				{
					possibility = getnextpossibility(e, current_room, \
							possibility);
					if (!checkway(*b, e->start->id, possibility))
					{
						ft_push_back(*b, &possibility);
						getways_rec(e, *b, possibility);
					}
					else
						ft_delete_container(b);
					ft_pop_back(begins);
				}
			}
			ft_delete_container(&begins);
		}
	}
}

void			getways(t_lemin *e)
{
	t_container	*w;

	if (!(w = ft_new_container(VECTOR, sizeof(size_t))))
		badalloc(__FILE__, __LINE__);
	getways_rec(e, w, e->start->id);
}
