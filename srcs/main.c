/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 11:32:11 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/24 13:16:36 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error(void)
{
	ft_putendl("ERROR");
	exit(EXIT_FAILURE);
}

void	badalloc(char *file, int line)
{
	ft_putstr("badalloc: ");
	ft_putstr(file);
	ft_putstr(" : ");
	ft_putnbr(line);
	ft_putchar('\n');
	exit(EXIT_FAILURE);
}

void	init(t_lemin *e)
{
	e->ants = LLONG_MIN;
	e->start = NULL;
	e->end = NULL;
	if (!(e->input = ft_new_container(VECTOR, sizeof(char *))))
		badalloc(__FILE__, __LINE__);
	if (!(e->rooms = ft_new_container(MAP, sizeof(t_room))))
		badalloc(__FILE__, __LINE__);
	if (!(e->rooms_ids = ft_new_container(VECTOR, sizeof(char *))))
		badalloc(__FILE__, __LINE__);
	e->adj_mat = NULL;
	if (!(e->ways = ft_new_container(VECTOR, sizeof(t_container *))))
		badalloc(__FILE__, __LINE__);
	e->stable_mat = NULL;
	e->endr.next_tab = NULL;
	e->endr.tab_size = 0;
	e->endr.arrived = 0;
}

void	free_memory(t_lemin *e)
{
	ft_set_content_destroy(e->input, (void (*)(void *))&free_input);
	ft_delete_container(&e->input);
	ft_set_content_destroy(e->rooms, (void (*)(void *))&free_room);
	ft_delete_container(&e->rooms);
	ft_delete_container(&e->rooms_ids);
	free(e->adj_mat[0]);
	free(e->adj_mat);
	ft_set_content_destroy(e->ways, (void(*)(void *))&ft_delete_container);
	ft_delete_container(&e->ways);
	free(e->stable_mat[0]);
	free(e->stable_mat);
	free_se(e);
	free_end_room(&e->endr);
}

int		main(void)
{
	t_lemin		e;
	size_t		wayset_id;

	init(&e);
	gethill(&e);
	checkhill(&e);
	getways(&e);
	wayset_id = stableresearch(&e);
	print_hill(&e);
	ants_run(&e, wayset_id);
	free_memory(&e);
	return (EXIT_SUCCESS);
}
