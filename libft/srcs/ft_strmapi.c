/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:43:38 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 15:48:17 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	len;
	char			*ptr;

	ptr = NULL;
	if (s && f)
	{
		len = ft_strlen(s);
		ptr = ft_strnew(len);
		if (ptr)
		{
			i = 0;
			while (s[i])
			{
				ptr[i] = f(i, s[i]);
				i++;
			}
		}
	}
	return (ptr);
}
