/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stable_research.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:29:00 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:33:21 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STABLE_RESEARCH_H
# define STABLE_RESEARCH_H

# include "lem_in.h"

void		create_stable_mat(t_lemin *e);
void		collision_check_fct1(t_context *context, size_t *id);
void		collision_check_fct0(t_context *context, size_t *id);
int			collision_check(t_lemin *e, t_container *way_y, t_container *way_x);
void		fill_stable_mat(t_lemin *e);
size_t		stable_sub_set_equality_collision(t_lemin *e, int **mat, \
					size_t y, size_t i[2]);
int			**stable_mat_cpy(t_lemin *e);

#endif
