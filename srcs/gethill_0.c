/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:22:39 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/24 13:38:01 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gethill.h"

void		get_room(t_lemin *e, char *line, t_room **sav)
{
	size_t	i;
	t_room	room;

	i = 0;
	while (line[i] && line[i] != ' ')
		++i;
	if (!line[i])
		error();
	if (!(room.name = ft_strsub(line, 0, i)))
		badalloc(__FILE__, __LINE__);
	room.id = ft_size(e->rooms);
	if (!room.name \
			|| !ft_strncmp(room.name, "L", 1) \
			|| (ft_sscanf(line + i, "%d %d", &room.pos_x, &room.pos_y) != 2) \
			|| room.pos_x < 0 \
			|| room.pos_y < 0)
		error();
	ft_insert(e->rooms, &room, room.name);
	ft_push_back(e->rooms_ids, &room.name);
	if (sav && !((*sav) = ft_memdup(&room, sizeof(t_room))))
		badalloc(__FILE__, __LINE__);
}

static int	get_pipe(t_lemin *e, char *line)
{
	t_pipe	pipe;
	size_t	i;
	size_t	sd;

	if (!(i = 0) && !e->adj_mat)
		create_adj_mat(e);
	while (line[i] && line[i] != '-')
		++i;
	if (!(pipe.in = ft_strsub(line, 0, i)))
		badalloc(__FILE__, __LINE__);
	if (!(sd = 0) && line[i])
		sd = ++i;
	while (line[i])
		++i;
	if (!(pipe.out = ft_strsub(line, sd, i - sd)))
		badalloc(__FILE__, __LINE__);
	if (i == sd || (i != sd && set_adj(e, pipe.in, pipe.out)))
	{
		free(pipe.in);
		free(pipe.out);
		return (1);
	}
	free(pipe.in);
	free(pipe.out);
	return (0);
}

static int	gethill_0(t_lemin *e, t_string *line, t_stream *stdin, t_bool *set)
{
	if (!((line->size = ft_stream_getline(stdin, &line->str)) > -1))
	{
		free(line->str);
		return (1);
	}
	ft_push_back(e->input, &line->str);
	if (ft_strncmp(line->str, "##", 2) && !ft_strncmp(line->str, "#", 1))
		(void)NULL;
	else if (!(*set) && (*set = D_TRUE))
		e->ants = ft_atoi(line->str);
	else if (!ft_strncmp(line->str, "##", 2))
	{
		if (iscmd(e, stdin, line->str))
			return (0);
	}
	else if (ispipe(line->str) || (e->adj_mat && ispipe(line->str)))
	{
		if (get_pipe(e, line->str))
			return (0);
	}
	else if (!ispipe(line->str) && !e->adj_mat)
		get_room(e, line->str, NULL);
	else
		return (0);
	return (1);
}

void		gethill(t_lemin *e)
{
	t_stream		*stdin;
	t_string		line;
	static t_bool	set = D_FALSE;

	line.str = NULL;
	stdin = ft_new_stream(0, 4096);
	while (ft_stream_good(stdin))
	{
		if (gethill_0(e, &line, stdin, &set))
			continue ;
		else
			break ;
	}
	ft_delete_stream(&stdin);
}
