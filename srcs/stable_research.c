/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stable_research.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 08:28:06 by bhivert           #+#    #+#             */
/*   Updated: 2016/06/11 15:37:29 by bhivert          ###   ########.fr       */
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
		e->stable_mat[i] = e->stable_mat[i - 1] + max_ways;
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

	if (way_y == way_x)
		return (1);
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

static int		**stable_mat_cpy(t_lemin *e)
{
	size_t	i;
	size_t	max_ways;
	int		**mat;

	i = 0;
	max_ways = ft_size(e->ways);
	if (!(mat = (int **)malloc(sizeof(int *) * max_ways)))
		badalloc(__FILE__, __LINE__);
	if (!(mat[0] = (int *)malloc(sizeof(int) * max_ways * max_ways)))
	{
		free(e->stable_mat);
		badalloc(__FILE__, __LINE__);
	}
	ft_memcpy(mat[0], e->stable_mat[0], sizeof(int) * max_ways * max_ways);
	while (++i < max_ways)
		mat[i] = mat[i - 1] + max_ways;
	return (mat);
}

static void		stable_sub_set_collision(t_lemin *e, int **mat)
{
	size_t	y;
	size_t	x;
	size_t	i;

	y = (size_t)-1;
	while (++y < ft_size(e->ways))
	{
		x = (size_t)-1;
		while (++x < ft_size(e->ways))
		{
			while (x < ft_size(e->ways) - 1 && e->stable_mat[y][x])
				++x;
			i = x;
			while (++i < ft_size(e->ways) && e->stable_mat[y][i])
			{
				if (1) //check collision
				{
				}
			}
		}
	}
}

static size_t	get_sum(t_lemin *e, size_t id)
{
	size_t	i;
	size_t	sum;

	i = -1;
	sum = 0;
	while (++i < ft_size(e->ways))
		sum += e->stable_mat[id][i];
	return (sum);
}

static size_t	get_collision(t_lemin *e, size_t id)
{
	size_t	i;
	size_t	collision;

	i = -1;
	collision = 0;
	while (++i < ft_size(e->ways))
	{
		if (!e->stable_mat[id][i])
			++collision;
	}
	return (collision);
}

static size_t	get_ways_set(t_lemin *e)
{
	t_wayset	set;
	t_wayset	tmp;
	size_t		y;

	y = -1;
	while (++y < ft_size(e->ways))
	{
		tmp = (t_wayset){y, get_collision(e, y), get_sum(e, y)};
		if (!y || tmp.collision < set.collision \
				|| (tmp.collision == set.collision && tmp.sum < set.sum))
			set = tmp;
	}
	return ((size_t)-1);
}

void		stableresearch(t_lemin *e)
{
	size_t	set;
	int		**mat_cpy;

	create_stable_mat(e);
	fill_stable_mat(e);
	mat_cpy = stable_mat_cpy(e);
	stable_sub_set_collision(e, mat_cpy);
	if ((set = get_ways_set(e)) == (size_t)-1)
		error();
}
