/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 12:31:45 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/27 13:10:37 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	if (n)
	{
		while (i < n)
		{
			a = ((unsigned char *)s1)[i];
			b = ((unsigned char *)s2)[i];
			if (a != b)
				return (a - b);
			i++;
		}
	}
	return (0);
}
