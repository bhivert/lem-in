/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getways.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:10:12 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:46:48 by bhivert          ###   ########.fr       */
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

#endif
