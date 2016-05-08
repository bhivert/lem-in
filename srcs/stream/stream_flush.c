/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/26 10:49:51 by bhivert           #+#    #+#             */
/*   Updated: 2016/02/26 10:59:16 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream_priv.h"

void	ft_stream_flush(t_stream *stream)
{
	ft_buff_flush(stream->buff, stream->fd, stream->flush);
}
