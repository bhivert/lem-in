/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_run_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:14:25 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:16:17 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
