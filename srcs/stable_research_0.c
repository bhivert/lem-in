/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stable_research.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 08:28:06 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:33:26 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stable_research.h"

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

size_t			stableresearch(t_lemin *e)
{
	size_t	set;
	int		**mat_cpy;

	create_stable_mat(e);
	fill_stable_mat(e);
	mat_cpy = stable_mat_cpy(e);
	stable_sub_set_collision(e, mat_cpy);
	free(mat_cpy[0]);
	free(mat_cpy);
	if ((set = get_ways_set(e)) == (size_t)-1)
		error();
	return (set);
}
