/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_priv.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 08:42:15 by bhivert           #+#    #+#             */
/*   Updated: 2016/03/16 14:07:21 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STREAM_PRIV_H
# define STREAM_PRIV_H

# include "stream.h"

typedef enum	e_state_index
{
	SI_GOOD = 0,
	SI_BAD,
	SI_EOF,
	SI_FAIL,
}				t_state_index;

#endif
