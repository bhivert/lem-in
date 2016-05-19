/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 11:32:46 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/15 10:23:43 by bhivert          ###   ########.fr       */
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

void			error(void);
void			badalloc(char *file, int line);

char			**split(const char *str, char c, size_t *size);
void			gethill(t_lemin *e);
void			checkhill(t_lemin *e);

#endif
