/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_priv.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 08:42:15 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:21:08 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STREAM_PRIV_H
# define STREAM_PRIV_H

# include "stream.h"
# include "bitset.h"

typedef enum	e_state_index
{
	SI_GOOD = 0,
	SI_BAD,
	SI_EOF,
	SI_FAIL,
}				t_state_index;

int			line_check(char c);
ssize_t		stream_line_alloc(t_stream *stream, char **line, size_t fact);
void		stream_in(t_stream *stream);

#endif
