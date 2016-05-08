/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitset.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/22 08:42:41 by bhivert           #+#    #+#             */
/*   Updated: 2016/03/30 20:38:14 by noxx             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITSET_H
# define BITSET_H

# include <stdlib.h>

int		bitset_reset(size_t *bitset);
int		bitset_set(size_t *bitset, size_t n);
int		bitset_unset(size_t *bitset, size_t n);
int		bitset_test(size_t bitset, size_t n);
int		bitset_none(size_t bitset);
int		bitset_any(size_t bitset);
size_t	bitset_size(void);

#endif
