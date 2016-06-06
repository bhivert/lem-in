/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 11:32:46 by bhivert           #+#    #+#             */
/*   Updated: 2016/06/06 11:29:55 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
# include <limits.h>
# include "libft.h"
# include "ft_containers.h"

typedef struct	s_string
{
	ssize_t		size;
	char		*str;
}				t_string;

typedef struct	s_room
{
	char		*name;
	size_t		id;
	int			pos_x;
	int			pos_y;
}				t_room;

typedef struct	s_pipe
{
	char		*in;
	char		*out;
}				t_pipe;

typedef struct	s_lemin
{
	t_int		ants;
	t_room		*start;
	t_room		*end;
	t_container	*rooms;
	t_container	*pipes;
	char		**adj_mat;
	t_container	*ways;
	int			**stable_mat;
}				t_lemin;

typedef struct	s_context
{
	size_t		start_id;
	size_t		end_id;
	size_t		id;
	t_container	*way;
	size_t		result;
}				t_context;

void			error(void);
void			badalloc(char *file, int line);

void			gethill(t_lemin *e);
void			checkhill(t_lemin *e);
void			getways(t_lemin *e);
void			stableresearch(t_lemin *e);

#endif
