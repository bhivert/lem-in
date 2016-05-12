/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:22:39 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/12 16:37:58 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "stream.h"
#include "ft_scanf.h"

static int	get_room(t_lemin *e, char *line, t_room **sav)
{
	size_t	i;
	t_room	room;

	i = 0;
	write(1, "666\n", 4);
	while (line[i] && line[i] != ' ')
		++i;
	if (!line[i])
		return (1);
	if (!(room.name = ft_strsub(line, 0, i)))
		badalloc(__FILE__, __LINE__);
	room.id = ft_size(e->rooms);
	if (!room.name \
			|| !ft_strncmp(room.name, "L", 1) \
			|| (ft_sscanf(line + i, "%d %d", &room.pos_x, &room.pos_y) != 2) \
			|| room.pos_x < 0 \
			|| room.pos_y < 0)
	{
		free(room.name);
		return (1);
	}
	if (!sav)
		ft_insert(e->rooms, &room, room.name);
	else
	{
		if (!(*sav = ft_memdup(&room, sizeof(t_room))))
			badalloc(__FILE__, __LINE__);
	}
	return (0);
}

static void	create_adj_mat(t_lemin *e)
{
	size_t	i;
	size_t	max_room;

	write(1, "555\n", 4);
	i = 0;
	max_room = ft_size(e->rooms);
	if (!(e->adj_mat = (char **)malloc(sizeof(char *) * max_room)))
		badalloc(__FILE__, __LINE__);
	if (!(e->adj_mat[0] = (char *)malloc(sizeof(char) * max_room * max_room)))
	{
		free(e->adj_mat);
		badalloc(__FILE__, __LINE__);
	}
	ft_memset(e->adj_mat[0], 0, max_room * max_room);
	while (++i < max_room)
		e->adj_mat[i] = e->adj_mat[i - 1] + max_room;
}

static void	set_adj(t_lemin *e, char *in, char *out)
{
	t_room	*in_room;
	t_room	*out_room;

	write(1, "444\n", 4);
	if (!(in_room = ft_at_key(e->rooms, in)))
		error();
	if (!(out_room = ft_at_key(e->rooms, out)))
		error();
	e->adj_mat[in_room->id][out_room->id] = 1;
	e->adj_mat[out_room->id][in_room->id] = 1;
}

static int	get_pipe(t_lemin *e, char *line)
{
	char	*in;
	char	*out;
	size_t	i;
	size_t	sd;

	write(1, "333\n", 4);
	i = 0;
	if (!e->adj_mat)
		create_adj_mat(e);
	while (line[i] && line[i] != '-')
		++i;
	if (!(in = ft_strsub(line, 0, i)))
		badalloc(__FILE__, __LINE__);
	if (line[i])
	{
		sd = ++i;
		while (line[i])
			++i;
		if (!(out = ft_strsub(line, sd, i - sd)))
		{
			free(in);
			badalloc(__FILE__, __LINE__);
		}
		set_adj(e, in, out);
		free(out);
	}
	else
		error();
	free(in);
	return (0);
}

static void	iscmd(t_lemin *e, t_stream *s, char *line)
{
	t_room		**tmp;
	t_string	l;

	write(1, "222\n", 4);
	tmp = NULL;
	if (!ft_strcmp(line, "##start") && !e->start)
		tmp = &e->start;
	else if (!ft_strcmp(line, "##end") && !e->end)
		tmp = &e->end;
	if (!tmp)
		error();
	if ((l.size = ft_stream_getline(s, &l.str) > -1))
		get_room(e, line, tmp);
}

static int	ispipe(char *line)
{
	size_t	i;
	write(1, "111\n", 4);

	i = 0;
	while (line[i] && line[i] != '-')
		++i;
	if (line[i] == '-')
		return (1);
	return (0);
}

void		gethill(t_lemin *e)
{
	t_stream	*stdin;
	t_string	line;

	write(1, "000\n", 4);
	stdin = ft_new_stream(0, 4096);
	while (ft_stream_good(stdin))
	{
		if ((line.size = ft_stream_getline(stdin, &line.str) > -1))
		{
			if (e->ants == (size_t)-1)
				e->ants = ft_atoi(line.str);
			else if (!ft_strncmp(line.str, "##", 2))
				iscmd(e, stdin, line.str);
			else if (!ft_strncmp(line.str, "#", 1))
				(void)NULL;
			else
			{
				if (ispipe(line.str) || (e->adj_mat && ispipe(line.str)))
					get_pipe(e, line.str);
				else if (!ispipe(line.str))
					get_room(e, line.str, NULL);
				else
					error();
			}
		}
		free(line.str);
	}
	ft_delete_stream(&stdin);
}
