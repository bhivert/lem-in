/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/07 11:32:46 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/12 16:25:04 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include <stdlib.h>
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
	size_t		ants;
	t_room		*start;
	t_room		*end;
	t_container	*rooms;
	char		**adj_mat;
	int			**stable_mat;
}				t_lemin;

void			error(void);
void			badalloc(char *file, int line);

char			**split(const char *str, char c, size_t *size);
void			gethill(t_lemin *e);

#endif
