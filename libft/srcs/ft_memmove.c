/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 09:24:03 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/27 10:53:21 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;

	if (dst <= src || dst >= (src + len))
		ft_memcpy(dst, src, len);
	else
	{
		s = (unsigned char *)src + (len - 1);
		d = (unsigned char *)dst + (len - 1);
		while (len--)
			*(d--) = *(s--);
	}
	return (dst);
}
