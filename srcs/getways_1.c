/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getways_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:09:28 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/24 10:07:26 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "getways.h"

size_t			getpossibility(t_lemin *e, size_t room)
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

size_t			getnextpossibility(t_lemin *e, size_t current_room, \
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

void			getways_rev_0(t_lemin *e, t_container *begins, \
		t_container **b, size_t possibility)
{
	if ((b = ft_at_index(begins, ft_size(begins) - 1)))
	{
		if (!checkway(*b, possibility))
			getways_rec(e, *b, possibility);
		else
			ft_delete_container(b);
		ft_pop_back(begins);
	}
}
