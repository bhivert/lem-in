/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gethill.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:22:49 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:49:47 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GETHILL_H
# define GETHILL_H

# include "lem_in.h"
# include "stream.h"
# include "ft_scanf.h"

void	create_adj_mat(t_lemin *e);
int		set_adj(t_lemin *e, char *in, char *out);
int		iscmd(t_lemin *e, t_stream *s, char *line);
int		ispipe(char *line);
void	get_room(t_lemin *e, char *line, t_room **sav);

#endif
