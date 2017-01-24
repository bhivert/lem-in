/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 10:42:24 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 10:42:30 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stream.h"

void	ft_delete_stream(t_stream **stream)
{
	free((*stream)->buff);
	free((*stream));
	*stream = NULL;
}
