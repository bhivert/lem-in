/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 10:45:42 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 10:45:45 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void	putinput(void *osef, char **line)
{
	(void)osef;
	ft_putendl(*line);
}

void		print_hill(t_lemin *e)
{
	ft_iter(e->input, NULL, (void(*)(void *, void *))&putinput);
	ft_putendl("");
}
