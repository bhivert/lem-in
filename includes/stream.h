/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 08:42:04 by bhivert           #+#    #+#             */
/*   Updated: 2016/05/08 09:35:05 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STREAM_H
# define STREAM_H

# include "libft.h"
# include "ft_containers.h"
# include "ft_buffers.h"

typedef struct	s_stream
{
	int			fd;
	size_t		buff_size;
	t_buff		*buff;
	size_t		state_bitset;
	ssize_t		(*sync)(int, void *, size_t);
	ssize_t		(*flush)(int, const void *, size_t);
}				t_stream;

t_stream		*ft_new_stream(int fd, size_t buff_size);
void			ft_delete_stream(t_stream **stream);
ssize_t			ft_stream_getline(t_stream *stream, char **line);

void			ft_stream_clear(t_stream *stream);
int				ft_stream_good(t_stream *stream);
int				ft_stream_bad(t_stream *stream);
int				ft_stream_fail(t_stream *stream);
int				ft_stream_eof(t_stream *stream);

void			ft_stream_out_str(t_stream *stream, char *str, size_t size);

#endif
