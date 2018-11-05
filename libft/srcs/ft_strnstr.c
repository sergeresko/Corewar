/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 10:38:33 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/30 12:29:14 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	t;

	i = 0;
	if (!s2[i])
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		j = 0;
		t = i;
		while (s1[i] && i < len && s1[i] == s2[j])
		{
			if (!s2[++j])
				return ((char *)s1 + t);
			i++;
		}
		i = t + 1;
	}
	return (NULL);
}
