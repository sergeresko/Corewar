/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:24:05 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 16:31:29 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_whitespace(int c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	int	start;
	int	end;

	if (s)
	{
		start = 0;
		end = ft_strlen(s) - 1;
		while (is_whitespace((unsigned char)s[start]))
			start++;
		if (start < end)
			while (is_whitespace((unsigned char)s[end]))
				end--;
		return (ft_strsub(s, start, (end - start + 1)));
	}
	return (NULL);
}
