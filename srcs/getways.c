/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getways.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/15 10:23:58 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/19 14:25:22 by bhivert          ###   ########.fr       */
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

static void		getways_rec(t_lemin *e, t_container *tbn, size_t current_room)
{
	size_t	i;
	size_t	possibility;

	i = (size_t)-1;
	possibility = getpossibility(e, current_room);
	while (++i < possibility)
	{
		if (!i)
			;
		else
			;
	}
}

void			getways(t_lemin *e)
{
	getways_rec(e, NULL, e->start->id);
}
