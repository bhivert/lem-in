/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:22:39 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/11 10:02:15 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "stream.h"
#include "ft_scanf.h"

static int	get_room(t_lemin *e, char *line)
{
	size_t	i;
	t_room	room;

	i = 0;
	while (line[i] && line[i] != ' ')
		++i;
	if (!line[i])
		return (1);
	room.name = ft_strsub(line, 0, i);
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
	ft_insert(e->rooms, &room, room.name);
	return (0);
}

static int	get_pipe(char *line)
{
	return (0);
}

static void	iscmd(t_lemin *e, t_stream *s, char *line)
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
	if ((l.size = ft_stream_getline(s, &l.str) > -1))
		(void)NULL; // get_room
}

void		gethill(t_lemin *e)
{
	size_t		i;
	t_stream	*stdin;
	t_string	line;

	i = 0;
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
			{}
		}
		free(line.str);
	}
	ft_delete_stream(&stdin);
}
