/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_getline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 13:10:30 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:20:22 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream_priv.h"

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
		if (((avail = ft_buff_in_avail(stream->buff))) > 0)
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
