/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:19:47 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 16:23:12 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*ptr;

	ptr = NULL;
	if (s1 && s2)
	{
		ptr = ft_strnew(ft_strlen(s1) + ft_strlen(s2));
		if (ptr)
		{
			i = 0;
			j = 0;
			while (s1[j])
				ptr[i++] = s1[j++];
			j = 0;
			while (s2[j])
				ptr[i++] = s2[j++];
		}
	}
	return (ptr);
}
