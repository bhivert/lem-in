/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stable_research.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 08:28:06 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/17 14:56:10 by bhivert          ###   ########.fr       */
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

static size_t	stable_sub_set_equality_collision(t_lemin *e, int **mat, \
					size_t y, size_t i[2])
{
	size_t	x_ncollision;
	size_t	i_ncollision;
	size_t	j;

	x_ncollision = 0;
	i_ncollision = 0;
	j = (size_t)-1;
	while (++j < ft_size(e->ways))
	{
		if (mat[y][j] && j != i[0] && !mat[j][i[0]])
			++x_ncollision;
	}
	j = (size_t)-1;
	while (++j < ft_size(e->ways))
	{
		if (mat[y][j] && j != i[1] && !mat[j][i[1]])
			++i_ncollision;
	}
	if (x_ncollision >= i_ncollision)
		return (0);
	return (1);
}

static void		stable_sub_set_collision(t_lemin *e, int **mat)
{
	size_t	y;
	size_t	i[2];
	size_t	tmp;

	y = (size_t)-1;
	while (++y < ft_size(e->ways))
	{
		i[0] = (size_t)-1;
		while (++i[0] < ft_size(e->ways))
		{
			if (!e->stable_mat[y][i[0]])
				continue ;
			i[1] = i[0];
			while (++i[1] < ft_size(e->ways))
			{
				if (!e->stable_mat[y][i[1]])
					continue ;
				if (!mat[i[0]][i[1]])
				{
					if (e->stable_mat[y][i[0]] > e->stable_mat[y][i[1]])
					{
						e->stable_mat[y][i[0]] = 0;
						break ;
					}
					else if (e->stable_mat[y][i[0]] < e->stable_mat[y][i[1]])
						e->stable_mat[y][i[1]] = 0;
					else
					{
						tmp = stable_sub_set_equality_collision(e, mat, y, i);
						e->stable_mat[y][i[tmp]] = 0;
						if (!tmp)
							break ;
					}
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
	if (!ft_size(e->ways))
		return ((size_t)-1);
	set = (t_wayset){0, 0, (size_t)-1};
	while (++y < ft_size(e->ways))
	{
		tmp = (t_wayset){y, get_collision(e, y), get_sum(e, y)};
		if (!y || tmp.collision < set.collision \
				|| (tmp.collision == set.collision && tmp.sum < set.sum))
			set = tmp;
	}
	return (set.id);
}

size_t		stableresearch(t_lemin *e)
{
	size_t	set;
	int		**mat_cpy;

	create_stable_mat(e);
	fill_stable_mat(e);
	mat_cpy = stable_mat_cpy(e);

// =============================================================================
	size_t	x, y;
//
//	ft_putchar('\n');
//	y = 0;
//	while (y < ft_size(e->ways))
//	{
//		x = 0;
//		while (x < ft_size(e->ways))
//		{
//			ft_putnbr(e->stable_mat[y][x]);
//			ft_putstr(" ");
//			++x;
//		}
//		ft_putchar('\n');
//		++y;
//	}
// =============================================================================

	stable_sub_set_collision(e, mat_cpy);

// =============================================================================
	ft_putchar('\n');
	y = 0;
	while (y < ft_size(e->ways))
	{
		x = 0;
		while (x < ft_size(e->ways))
		{
			ft_putnbr(e->stable_mat[y][x]);
			ft_putstr(" ");
			++x;
		}
		ft_putchar('\n');
		++y;
	}
// =============================================================================

	if ((set = get_ways_set(e)) == (size_t)-1)
		error();
	// <===
	return (set);
}
