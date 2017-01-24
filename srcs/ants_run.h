/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants_run.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:14:51 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/24 10:54:23 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANTS_RUN_H
# define ANTS_RUN_H

# include "lem_in.h"

t_run_room	*new_run_room(t_lemin *e, size_t room_id);
void		fill_active_ways(t_lemin *e, t_container *active_ways, \
		size_t wayset);
void		ants_run_loop_0(t_lemin *e, t_run_room *tmp, \
		t_int *last_id, size_t i);
void		ants_run_loop_1(t_run_room *tmp);

#endif
