/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getways.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:10:12 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/24 10:06:02 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETWAYS_H
# define GETWAYS_H

# include "lem_in.h"

size_t			getpossibility(t_lemin *e, size_t room);
t_container		*create_begins(t_lemin *e, t_container *current_way, \
					size_t current_room);
size_t			getnextpossibility(t_lemin *e, size_t current_room, \
					size_t last_possibility);
void			getways_rec(t_lemin *e, t_container *current_way, \
					size_t current_room);
void			getways_rev_0(t_lemin *e, t_container *begins, \
					t_container **b, size_t possibility);
size_t			checkway(t_container *way, size_t room);

#endif
