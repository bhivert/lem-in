/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethill_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:23:30 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:51:12 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gethill.h"

void	create_adj_mat(t_lemin *e)
{
	size_t	i;
	size_t	max_room;

	i = 0;
	max_room = ft_size(e->rooms);
	if (!(e->adj_mat = (char **)malloc(sizeof(char *) * max_room)))
		badalloc(__FILE__, __LINE__);
	if (!(e->adj_mat[0] = (char *)malloc(sizeof(char) * max_room * max_room)))
	{
		free(e->adj_mat);
		badalloc(__FILE__, __LINE__);
	}
	ft_memset(e->adj_mat[0], 0, sizeof(char) * max_room * max_room);
	while (++i < max_room)
		e->adj_mat[i] = e->adj_mat[i - 1] + max_room;
}

int		set_adj(t_lemin *e, char *in, char *out)
{
	t_room	*in_room;
	t_room	*out_room;

	if (!(in_room = ft_at_key(e->rooms, in)))
		return (1);
	if (!(out_room = ft_at_key(e->rooms, out)))
		return (1);
	e->adj_mat[in_room->id][out_room->id] = 1;
	e->adj_mat[out_room->id][in_room->id] = 1;
	return (0);
}

int		iscmd(t_lemin *e, t_stream *s, char *line)
{
	t_room		**tmp;
	t_string	l;

	tmp = NULL;
	if (!ft_strcmp(line, "##start") && !e->start)
		tmp = &e->start;
	else if (!ft_strcmp(line, "##end") && !e->end)
		tmp = &e->end;
	if (!tmp)
		error();
	if ((l.size = ft_stream_getline(s, &l.str)) > -1)
	{
		ft_push_back(e->input, &l.str);
		get_room(e, l.str, tmp);
	}
	return (0);
}

int		ispipe(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '-')
		++i;
	if (line[i] == '-')
		return (1);
	return (0);
}
