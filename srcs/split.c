/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bhivert <bhivert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 09:22:35 by bhivert           #+#    #+#             */
/*   Updated: 2016/03/20 14:56:04 by bhivert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	split_word_count(const char *str, char c)
{
	size_t	i;
	size_t	nword;
	size_t	word_len;

	i = 0;
	nword = 0;
	while (str[i])
	{
		word_len = 0;
		while (str[i + word_len] && str[i + word_len] != c)
			++word_len;
		if (word_len > 0)
			++nword;
		i += (word_len > 0) ? word_len : 1;
	}
	return (nword);
}

static char		*split_get_next_word(const char *str, char c, size_t *offset)
{
	size_t	len;
	char	*word;

	len = 0;
	while (str[*offset] && str[*offset] == c)
		++(*offset);
	if (!str[*offset])
		return (ft_strnew(1));
	while (str[*offset + len] && str[*offset + len] != c)
		++len;
	word = ft_strsub(str, *offset, len);
	(*offset) += len;
	return (word);
}

char			**split(const char *str, char c, size_t *size)
{
	char	**split;
	size_t	i;
	size_t	offset;

	split = NULL;
	i = -1;
	offset = 0;
	*size = split_word_count(str, c);
	if ((split = (char **)malloc(sizeof(char *) * (*size + 1))))
	{
		while (++i < *size)
		{
			if (!(split[i] = split_get_next_word(str, c, &offset)))
			{
				while (--i != (size_t)-1)
					free(split[i]);
				free(split);
				return (NULL);
			}
		}
		split[*size] = NULL;
	}
	return (split);
}
