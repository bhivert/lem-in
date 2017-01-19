/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:22:39 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/19 19:01:49 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "stream.h"
#include "ft_scanf.h"

static void	get_room(t_lemin *e, char *line, t_room **sav)
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

static void	create_adj_mat(t_lemin *e)
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

static int	set_adj(t_lemin *e, char *in, char *out)
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

static int	get_pipe(t_lemin *e, char *line)
{
	t_pipe	pipe;
	size_t	i;
	size_t	sd;

	i = 0;
	if (!e->adj_mat)
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
	ft_push_back(e->pipes, &pipe);
	return (0);
}

static int	iscmd(t_lemin *e, t_stream *s, char *line)
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

static int	ispipe(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '-')
		++i;
	if (line[i] == '-')
		return (1);
	return (0);
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
		if (!((line.size = ft_stream_getline(stdin, &line.str)) > -1))
			continue ;
		ft_push_back(e->input, &line.str);
		if (ft_strncmp(line.str, "##", 2) && !ft_strncmp(line.str, "#", 1))
			(void)NULL;
		else if (!set && (set = D_TRUE))
			e->ants = ft_atoi(line.str);
		else if (!ft_strncmp(line.str, "##", 2))
		{
			if (iscmd(e, stdin, line.str))
				break ;
		}
		else if (ispipe(line.str) || (e->adj_mat && ispipe(line.str)))
		{
			if (get_pipe(e, line.str))
				break ;
		}
		else if (!ispipe(line.str) && !e->adj_mat)
			get_room(e, line.str, NULL);
		else
			break ;
	}
	ft_delete_stream(&stdin);
}
