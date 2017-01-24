/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stable_research_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:32:20 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/24 11:01:32 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stable_research.h"

int		**stable_mat_cpy(t_lemin *e)
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

size_t	stable_sub_set_equality_collision(t_lemin *e, int **mat, \
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

int		stable_sub_set_collision_0(t_lemin *e, int **mat, \
		size_t *i, size_t y)
{
	size_t	tmp;

	if (e->stable_mat[y][i[0]] > e->stable_mat[y][i[1]])
	{
		e->stable_mat[y][i[0]] = 0;
		return (1);
	}
	else if (e->stable_mat[y][i[0]] < e->stable_mat[y][i[1]])
		e->stable_mat[y][i[1]] = 0;
	else
	{
		tmp = stable_sub_set_equality_collision(e, mat, y, i);
		e->stable_mat[y][i[tmp]] = 0;
		if (!tmp)
			return (1);
	}
	return (0);
}
