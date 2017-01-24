/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_run.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:43:46 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/24 13:25:18 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static void	fill_active_ways(t_lemin *e, t_container *active_ways, \
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

static t_run_room	*new_run_room(t_lemin *e, size_t room_id)
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

static void	i_room(void **context, size_t *room_id)
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

static void	i_ways(void **context, size_t *way_id)
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
	end->weight_tab[*i] = ft_size(way) - 2;
}

void		ants_run_init(t_lemin* e, t_run_end *end, size_t wayset_id)
{
	t_container	*active_ways;
	size_t		i;
	void		*context[3];

	i = (size_t)-1;
	if (!(active_ways = ft_new_container(VECTOR, sizeof(size_t))))
		badalloc(__FILE__, __LINE__);
	fill_active_ways(e, active_ways, wayset_id);
	end->next_tab = (t_run_room **)malloc(sizeof(t_run_room) \
			* ft_size(active_ways));
	end->weight_tab = (size_t *)malloc(sizeof(size_t) * ft_size(active_ways));
	ft_memset(end->next_tab, 0, sizeof(t_run_room) * ft_size(active_ways));
	end->tab_size = ft_size(active_ways);
	end->arrived = 0;
	if (!end->next_tab || !end->weight_tab)
		badalloc(__FILE__, __LINE__);
	context[0] = e;
	context[1] = end;
	context[2] = &i;
	ft_iter(active_ways, context, (void(*)(void *, void *))&i_ways);
// <<< ================ SORT == OR SEE FOR INSERTION SORT ======================

// =============================================================================
//	t_run_room	*tmp;
//	size_t	j = (size_t)-1;
//	while (++j < end->tab_size)
//	{
//		tmp = end->next_tab[j];
//		ft_printf("\n============\n");
//		while (tmp)
//		{
//			ft_printf("%zu: %s (%zu)\n", tmp->room->id, tmp->room->name, tmp->ant_id);
//			tmp = tmp->next;
//		}
//	}
// =============================================================================
}

void	ants_run(t_lemin *e, size_t wayset_id)
{
	t_run_end	end;
	t_int		last_id;
	size_t		i;
	t_run_room	*tmp;

	last_id = 0;
	ants_run_init(e, &end, wayset_id);
	while (end.arrived < e->ants)
	{
		i = 0;
		while (i < end.tab_size)
		{
			tmp = end.next_tab[i];
			while (tmp)
			{
				if (tmp == end.next_tab[i] && !tmp->next && ++end.arrived)
				{
					if (last_id < e->ants)
						ft_printf("L%lld-%s ", ++last_id, e->end->name);
				}
				else if (tmp == end.next_tab[i])
				{
					if (tmp->next->ant_id != (size_t)-1 && ++end.arrived)
					{
						ft_printf("L%lld-%s ", tmp->next->ant_id, e->end->name);
						tmp->next->ant_id = (size_t)-1;
					}
				}
				else if (!tmp->next)
				{
					if (last_id < e->ants)
					{
						ft_printf("L%lld-%s ", ++last_id, tmp->room->name);
						tmp->ant_id = last_id;
					}
				}
				else
				{
					if (tmp->next->ant_id != (size_t)-1)
					{
						ft_printf("L%lld-%s ", tmp->next->ant_id, tmp->room->name);
						tmp->ant_id = tmp->next->ant_id;
						tmp->next->ant_id = (size_t)-1;
					}
				}
				tmp = tmp->next;
			}
			++i;
		}
		ft_putendl("");
	}
}
