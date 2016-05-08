/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 12:22:39 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/08 16:01:16 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "stream.h"

static int	check_room(char *line)
{
	size_t	i;
	size_t	size;
	char	**sp;

	i = 0;
	if ((sp = split(line, ' ', &size)))
	{
		while (sp[i])
			free(sp[i]);
		free(sp);
	}
	if (size == 3)
		return (1);
	return (0);
}

static void	iscmd(t_lemin *e, char *line)
{
	t_room	**tmp;
	char	*l;

	tmp = NULL;
	if (!ft_strcmp(line, "##start") && !e->start)
		tmp = &e->start;
	else if (!ft_strcmp(line, "##end") && !e->end)
		tmp = &e->end;
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
			{
				;
			}
			else if (!ft_strncmp(line.str, "#", 1))
				(void)NULL;
			else
			{}
		}
		free(line.str);
	}
	ft_delete_stream(&stdin);
}
