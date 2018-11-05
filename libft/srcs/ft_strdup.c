/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:57:23 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 17:02:05 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	unsigned int	len;
	char			*ptr;

	if (s1)
	{
		len = ft_strlen(s1);
		if ((ptr = ft_strnew(len)))
			return (ft_strcpy(ptr, s1));
	}
	return (NULL);
}
