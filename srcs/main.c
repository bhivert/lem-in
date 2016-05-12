/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 11:32:11 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/12 13:03:04 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init(t_lemin *e)
{
	e->ants = (size_t)-1;
	e->start = NULL;
	e->end = NULL;
	e->rooms = ft_new_container(MAP, sizeof(t_room));
	e->adj_mat = NULL;
	e->stable_mat = NULL;
}

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

int		main(void)
{
	t_lemin		e;

	init(&e);
	return (EXIT_SUCCESS);
}
