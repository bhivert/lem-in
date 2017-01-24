/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 08:45:28 by bhivert           #+#    #+#             */
/*   Updated: 2017/01/23 11:06:16 by bhivert          ###   ########.fr       */
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
