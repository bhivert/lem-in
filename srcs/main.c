/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 11:32:11 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/19 09:40:02 by bhivert          ###   ########.fr       */
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
	if (!(e->rooms = ft_new_container(MAP, sizeof(t_room))))
		badalloc(__FILE__, __LINE__);
	if (!(e->pipes = ft_new_container(DEQUE, sizeof(t_pipe))))
		badalloc(__FILE__, __LINE__);
	e->adj_mat = NULL;
	if (!(e->ways = ft_new_container(VECTOR, sizeof(t_container *))))
		badalloc(__FILE__, __LINE__);
	e->stable_mat = NULL;
}

int		main(void)
{
	t_lemin		e;

	init(&e);
	gethill(&e);
	checkhill(&e);

	size_t	x, y;

	x = 0;
	while (x < ft_size(e.rooms))
	{
		y = 0;
		while (y < ft_size(e.rooms))
		{
			ft_putnbr(e.adj_mat[y][x]);
			ft_putstr(" ");
			++y;
		}
		ft_putchar('\n');
		++x;
	}
	return (EXIT_SUCCESS);
}
