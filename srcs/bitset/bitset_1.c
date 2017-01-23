/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 11:04:57 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:06:09 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitset.h"

int		bitset_none(size_t bitset)
{
	if (!bitset)
		return (1);
	return (0);
}

int		bitset_any(size_t bitset)
{
	int		rs;

	rs = bitset_none(bitset);
	return (!rs);
}

size_t	bitset_size(void)
{
	return (sizeof(size_t) << 3);
}
