/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:55:10 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 15:58:08 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	unsigned int i;

	if (s1 && s2)
	{
		i = 0;
		while ((s1[i] || s2[i]) && (i < n))
		{
			if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}
