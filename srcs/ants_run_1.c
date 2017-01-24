/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_run_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:14:25 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/24 10:54:30 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void		fill_active_ways(t_lemin *e, t_container *active_ways, \
		size_t wayset)
{
	size_t	nways;
	size_t	x;

	nways = ft_size(e->ways);
	x = (size_t)-1;
	ft_push_back(active_ways, &wayset);
	while (++x < nways)
	{
		if (e->stable_mat[wayset][x] != 0)
			ft_push_back(active_ways, &x);
	}
}

t_run_room	*new_run_room(t_lemin *e, size_t room_id)
{
	t_run_room	*new;
	char		*room_name;
	t_room		*room;

	if (!(new = (t_run_room *)malloc(sizeof(t_run_room))))
		badalloc(__FILE__, __LINE__);
	room_name = *(char **)ft_at_index(e->rooms_ids, room_id);
	room = (t_room *)ft_at_key(e->rooms, room_name);
	*new = (t_run_room){NULL, room, (size_t)-1};
	return (new);
}

void		ants_run_loop_1(t_run_room *tmp)
{
	if (tmp->next->ant_id != (size_t)-1)
	{
		ft_printf("L%lld-%s ", tmp->next->ant_id, tmp->room->name);
		tmp->ant_id = tmp->next->ant_id;
		tmp->next->ant_id = (size_t)-1;
	}
}

void		ants_run_loop_0(t_lemin *e, t_run_room *tmp, \
		t_int *last_id, size_t i)
{
	if (tmp == e->endr.next_tab[i] && !tmp->next && ++e->endr.arrived)
	{
		if (*last_id < e->ants)
			ft_printf("L%lld-%s ", ++(*last_id), e->end->name);
	}
	else if (tmp == e->endr.next_tab[i])
	{
		if (tmp->next->ant_id != (size_t)-1 && ++e->endr.arrived)
		{
			ft_printf("L%lld-%s ", tmp->next->ant_id, e->end->name);
			tmp->next->ant_id = (size_t)-1;
		}
	}
	else if (!tmp->next)
	{
		if (*last_id < e->ants)
		{
			ft_printf("L%lld-%s ", ++(*last_id), tmp->room->name);
			tmp->ant_id = *last_id;
		}
	}
	else
		ants_run_loop_1(tmp);
}
