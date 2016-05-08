/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 13:09:08 by bhivert           #+#    #+#             */
/*   Updated: 2016/04/04 17:03:35 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream_priv.h"
#include "bitset.h"

t_stream	*ft_new_stream(int fd, size_t buff_size)
{
	t_stream	*stream;

	if (fd < 0 || !buff_size)
		return (NULL);
	if (!(stream = (t_stream *)malloc(sizeof(t_stream))))
		return (NULL);
	if (!(stream->buff = ft_new_buff(buff_size)))
	{
		free(stream);
		return (NULL);
	}
	stream->fd = fd;
	stream->buff_size = buff_size;
	bitset_reset(&stream->state_bitset);
	bitset_set(&stream->state_bitset, SI_GOOD);
	stream->sync = &read;
	stream->flush = &write;
	return (stream);
}
