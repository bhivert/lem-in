/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 11:32:11 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/19 17:40:09 by bhivert          ###   ########.fr       */
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
//	if (!(e->rooms_ids = ft_new_container(VECTOR, sizeof(char *))))
//		badalloc(__FILE__, __LINE__);
	if (!(e->pipes = ft_new_container(DEQUE, sizeof(t_pipe))))
		badalloc(__FILE__, __LINE__);
	e->adj_mat = NULL;
	if (!(e->ways = ft_new_container(VECTOR, sizeof(t_container *))))
		badalloc(__FILE__, __LINE__);
	e->stable_mat = NULL;
}

static void	putri(char **n)
{
	ft_putstr(*n);
}
////static void	putr(t_room *r)
//{
//	ft_putstr(r->name);
//	ft_putstr(" id = ");
//	ft_putnbr(r->id);
//}
//
//static void	putw(size_t *r)
//{
//	ft_putchar(' ');
//	ft_putnbr(*r);
//}
//
//static void	put(t_container **c)
//{
//	ft_debug_container(*c, (void(*)(void *))&putw);
//	ft_putchar('\n');
//}

# include "ft_printf.h"
int		main(void)
{
	t_lemin		e;
	size_t		wayset_id;

	ft_printf("000\n");
	init(&e);
	ft_printf("111\n");
	gethill(&e);
	ft_printf("222\n");
	checkhill(&e);
	ft_printf("333\n");
	getways(&e);
	ft_printf("444\n");
	wayset_id = stableresearch(&e);
	ft_printf("555\n");
	print_hill(&e);
	ft_printf("666\n");
	ants_run(&e, wayset_id);

// =============================================================================

//	ft_debug_container(e.rooms_ids, (void(*)(void *))&putri);
//	ft_debug_container(e.rooms, (void(*)(void *))&putr);
//	ft_debug_container(e.ways, (void(*)(void *))&put);

//	size_t	x, y;

//	y = 0;
//	while (y < ft_size(e.rooms))
//	{
//		x = 0;
//		while (x < ft_size(e.rooms))
//		{
//			ft_putnbr(e.adj_mat[y][x]);
//			ft_putstr(" ");
//			++x;
//		}
//		ft_putchar('\n');
//		++y;
//	}

//	ft_putchar('\n');
//	y = 0;
//	while (y < ft_size(e.ways))
//	{
//		x = 0;
//		while (x < ft_size(e.ways))
//		{
//			ft_putnbr(e.stable_mat[y][x]);
//			ft_putstr(" ");
//			++x;
//		}
//		ft_putchar('\n');
//		++y;
//	}

//	ft_printf("%zu\n", wayset_id);

// =============================================================================

	return (EXIT_SUCCESS);
}
