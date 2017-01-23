/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory_fct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 12:52:09 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 16:53:18 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_input(char **line)
{
	free(*line);
}

void	free_room(t_room *room)
{
	free(room->name);
}

void	free_se(t_lemin *e)
{
	if (e->start)
		free(e->start);
	if (e->end)
		free(e->end);
}

void	free_end_room(t_run_end *end)
{
	size_t	i;

	i = (size_t)-1;
	while (++i < end->tab_size)
		ft_lstdel((t_list **)&end->next_tab[i], &free);
	free(end->next_tab);
}
