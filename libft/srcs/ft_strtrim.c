/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:24:05 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/06 19:20:15 by ozalisky         ###   ########.fr       */
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

static int	is_whitespace_multi(int c)
{
	if (c == '\n')
		return (1);
	return (0);
}

char		*ft_strtrim_multi(char const *s)
{
	int	start;
	int	end;

	if (s)
	{
		start = 0;
		end = ft_strlen(s) - 1;
		while (is_whitespace_multi((unsigned char)s[start]))
			start++;
		if (start < end)
			while (is_whitespace_multi((unsigned char)s[end]))
				end--;
		return (ft_strsub(s, start, (end - start + 1)));
	}
	return (NULL);
}
