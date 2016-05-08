/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_getline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 13:10:30 by bhivert           #+#    #+#             */
/*   Updated: 2016/03/17 11:46:27 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream_priv.h"
#include "bitset.h"

static int		line_check(char c)
{
	return ((c == '\n'));
}

static ssize_t	stream_line_alloc(t_stream *stream, char **line, size_t fact)
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

void			stream_in(t_stream *stream)
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

static void		ft_stream_getline_norme0(t_stream *stream, char **line, \
					ssize_t *tmp, size_t *size)
{
	*size += ft_abs(*tmp);
	(*line)[*size] = '\0';
	ft_buff_flush(stream->buff, -1, NULL);
}

static ssize_t	ft_stream_getline_norme1(t_stream *stream, char **line, \
					ssize_t *tmp, size_t *size)
{
	*size += *tmp;
	(*line)[*size] = '\0';
	ft_buff_flush_n(stream->buff, 1, -1, NULL);
	return (*size);
}

ssize_t			ft_stream_getline(t_stream *stream, char **line)
{
	size_t	avail;
	ssize_t	tmp;
	size_t	fact;
	size_t	size;

	size = 0;
	*line = NULL;
	fact = stream_line_alloc(stream, line, 0);
	while (ft_stream_good(stream))
	{
		if ((avail = ft_buff_in_avail(stream->buff)) > 0)
		{
			tmp = ft_buff_get_check(stream->buff, (*line) + size, \
					(stream->buff_size * fact) - size, &line_check);
			if (!(tmp < 0))
				return (ft_stream_getline_norme1(stream, line, &tmp, &size));
			ft_stream_getline_norme0(stream, line, &tmp, &size);
			if (!(size < stream->buff_size * fact))
				fact = stream_line_alloc(stream, line, fact);
		}
		else
			stream_in(stream);
	}
	return (-1);
}
