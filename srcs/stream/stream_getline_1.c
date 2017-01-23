/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_getline_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:18:46 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:20:30 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream_priv.h"

int			line_check(char c)
{
	return ((c == '\n'));
}

ssize_t		stream_line_alloc(t_stream *stream, char **line, size_t fact)
{
	char	*tmp;

	++fact;
	if (!(tmp = (char *)malloc(sizeof(char) * (stream->buff_size * fact + 1))))
		return (-1);
	ft_memcpy(tmp, *line, stream->buff_size * (fact - 1));
	free(*line);
	*line = tmp;
	return (fact);
}

void		stream_in(t_stream *stream)
{
	ssize_t		out;

	if ((out = ft_buff_in(stream->buff, stream->fd, stream->sync)) < 0)
	{
		bitset_set(&stream->state_bitset, SI_BAD);
		bitset_set(&stream->state_bitset, SI_FAIL);
		bitset_unset(&stream->state_bitset, SI_GOOD);
	}
	else if (!out && !ft_buff_in_avail(stream->buff))
	{
		bitset_set(&stream->state_bitset, SI_EOF);
		bitset_set(&stream->state_bitset, SI_BAD);
		bitset_unset(&stream->state_bitset, SI_GOOD);
	}
}
