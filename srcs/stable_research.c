/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stable_research.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 08:28:06 by bhivert           #+#    #+#             */
/*   Updated: 2016/06/06 12:33:21 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	create_stable_mat(t_lemin *e)
{
	size_t	i;
	size_t	max_ways;

	i = 0;
	max_ways = ft_size(e->ways);
	if (!(e->stable_mat = (int **)malloc(sizeof(int *) * max_ways)))
		badalloc(__FILE__, __LINE__);
	if (!(e->stable_mat[0] = (int *)malloc(sizeof(int) * max_ways * max_ways)))
	{
		free(e->stable_mat);
		badalloc(__FILE__, __LINE__);
	}
	ft_memset(e->stable_mat[0], 0, sizeof(int) * max_ways * max_ways);
	while (++i < max_ways)
		e->stable_mat[i] = e->stable_mat[i - 1] + (sizeof(int) * max_ways);
}

static void	collision_check_fct1(t_context *context, size_t *id)
{
	if (context->start_id != context->id && context->end_id != context->id \
			&& context->start_id != *id && context->end_id != *id \
			&& context->id == *id)
		context->result = 1;
}

static void	collision_check_fct0(t_context *context, size_t *id)
{
	context->id = *id;
	ft_iter(context->way, context, (void(*)(void *, void *))&collision_check_fct1);
}

static int	collision_check(t_lemin *e, t_container *way_y, t_container *way_x)
{
	t_context	context;

	context.start_id = e->start->id;
	context.end_id = e->end->id;
	context.id = (size_t)-1;
	context.way = way_x;
	context.result = 0;
	ft_iter(way_y, &context, (void(*)(void *, void *))&collision_check_fct0);
	return (context.result);
}

static void	fill_stable_mat(t_lemin *e)
{
	size_t		x;
	size_t		y;
	t_container	**way_x;
	t_container	**way_y;

	y = -1;
	while (++y < ft_size(e->ways))
	{
		x = -1;
		way_y = ft_at_index(e->ways, y);
		while (++x < ft_size(e->ways))
		{
			way_x = ft_at_index(e->ways, x);
			if (!collision_check(e, *way_y, *way_x))
				e->stable_mat[y][x] = ft_size(*way_y) + ft_size(*way_x) - 4;
		}
	}
}

void		stableresearch(t_lemin *e)
{
	create_stable_mat(e);
	fill_stable_mat(e);
}
