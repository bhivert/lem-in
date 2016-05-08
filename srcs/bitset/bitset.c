/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 08:45:28 by bhivert           #+#    #+#             */
/*   Updated: 2016/03/16 14:13:32 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitset.h"

int		bitset_reset(size_t *bitset)
{
	if (bitset)
		return ((*bitset ^= *bitset));
	return (-1);
}

int		bitset_set(size_t *bitset, size_t n)
{
	if (bitset && (n < (sizeof(size_t) << 3)))
	{
		*bitset |= (1 << n);
		return (0);
	}
	return (-1);
}

int		bitset_unset(size_t *bitset, size_t n)
{
	if (bitset && (n < (sizeof(size_t) << 3)))
	{
		*bitset &= ~(1 << n);
		return (0);
	}
	return (-1);
}

int		bitset_test(size_t bitset, size_t n)
{
	if (n < (sizeof(size_t) << 3))
		return ((bitset & (1 << n)) >> n);
	return (-1);
}

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
