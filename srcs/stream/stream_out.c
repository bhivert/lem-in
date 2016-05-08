/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 11:29:48 by bhivert           #+#    #+#             */
/*   Updated: 2016/02/26 12:10:41 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream_priv.h"
#include "bitset.h"

void	ft_stream_out_str(t_stream *stream, char *str, size_t size)
{
	size_t		out;
	ssize_t		err;

	out = 0;
	while (ft_stream_good(stream) && out < size)
	{
		err = stream->flush(stream->fd, str, size);
		if (err < 0)
		{
			bitset_set(&stream->state_bitset, SI_BAD);
			bitset_set(&stream->state_bitset, SI_FAIL);
			bitset_unset(&stream->state_bitset, SI_GOOD);
		}
		else
			out += err;
	}
}
