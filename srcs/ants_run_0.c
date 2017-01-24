/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:43:46 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/24 13:15:02 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ants_run.h"

static void			i_room(void **context, size_t *room_id)
{
	t_lemin		*e;
	t_run_end	*end;
	size_t		i;
	t_run_room	*room;

	e = (t_lemin *)context[0];
	if (*room_id != e->start->id)
	{
		end = (t_run_end *)context[1];
		i = *(size_t *)context[2];
		room = new_run_room(e, *room_id);
		ft_lstadd((t_list **)&end->next_tab[i], room);
	}
}

static void			i_ways(void **context, size_t *way_id)
{
	t_lemin		*e;
	t_run_end	*end;
	size_t		*i;
	t_container	*way;

	e = (t_lemin *)context[0];
	end = (t_run_end *)context[1];
	i = (size_t *)context[2];
	++(*i);
	way = *(t_container **)ft_at_index(e->ways, *way_id);
	ft_iter(way, context, (void(*)(void *, void *))&i_room);
}

void				ants_run_init(t_lemin *e, size_t wayset_id)
{
	t_container	*active_ways;
	size_t		i;
	void		*context[3];

	i = (size_t)-1;
	if (!(active_ways = ft_new_container(VECTOR, sizeof(size_t))))
		badalloc(__FILE__, __LINE__);
	fill_active_ways(e, active_ways, wayset_id);
	e->endr.next_tab = (t_run_room **)malloc(sizeof(t_run_room) \
			* ft_size(active_ways));
	ft_memset(e->endr.next_tab, 0, sizeof(t_run_room) * ft_size(active_ways));
	e->endr.tab_size = ft_size(active_ways);
	if (!e->endr.next_tab)
		badalloc(__FILE__, __LINE__);
	context[0] = e;
	context[1] = &e->endr;
	context[2] = &i;
	ft_iter(active_ways, context, (void(*)(void *, void *))&i_ways);
	ft_delete_container(&active_ways);
}

void				ants_run(t_lemin *e, size_t wayset_id)
{
	t_int		last_id;
	size_t		i;
	t_run_room	*tmp;

	last_id = 0;
	ants_run_init(e, wayset_id);
	while (e->endr.arrived < e->ants)
	{
		i = 0;
		while (i < e->endr.tab_size)
		{
			tmp = e->endr.next_tab[i];
			while (tmp)
			{
				ants_run_loop_0(e, tmp, &last_id, i);
				tmp = tmp->next;
			}
			++i;
		}
		ft_putendl("");
	}
}
