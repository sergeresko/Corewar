/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:15:24 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 16:19:28 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (s)
	{
		ptr = ft_strnew(len);
		if (ptr)
		{
			while (i < len && s[start])
				ptr[i++] = s[start++];
		}
	}
	return (ptr);
}
