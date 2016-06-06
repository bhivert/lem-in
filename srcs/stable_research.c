/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stable_research.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/06 08:28:06 by bhivert           #+#    #+#             */
/*   Updated: 2016/06/06 09:34:14 by bhivert          ###   ########.fr       */
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
		badalloc(__FILE__, __LINE__);
	ft_memset(e->stable_mat, 0, max_ways * max_ways);
	while (++i < max_ways)
		e->stable_mat[i] = e->stable_mat[i - 1] + max_ways;
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
			// colision check
		}
	}
}

void		stableresearch(t_lemin *e)
{
	create_stable_mat(e);
	fill_stable_mat(e);
}
