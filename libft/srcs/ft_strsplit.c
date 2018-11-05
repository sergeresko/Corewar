/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 10:26:46 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/30 10:36:45 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_count(char const *s, char c)
{
	int		is_in;
	size_t	i;
	size_t	words;

	i = 0;
	is_in = 0;
	words = 0;
	while (s[i])
	{
		if (!is_in && s[i] != c)
		{
			words++;
			is_in = 1;
		}
		if (s[i] == c)
			is_in = 0;
		i++;
	}
	return (words);
}

static void	str_write(char **array, char const *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	size;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			size = 0;
			start = i;
			while (s[i] != c && s[i] != '\0')
			{
				size++;
				i++;
			}
			array[j++] = ft_strsub(s, start, size);
			continue ;
		}
		i++;
	}
}

char		**ft_strsplit(char const *s, char c)
{
	size_t	size;
	char	**array;

	array = NULL;
	if (s)
	{
		size = str_count(s, c);
		array = (char **)malloc(sizeof(char *) * (size + 1));
		if (array)
		{
			array[size] = NULL;
			str_write(array, s, c);
		}
	}
	return (array);
}
