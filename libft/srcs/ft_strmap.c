/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:35:31 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 15:47:01 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
				ptr[i] = f(s[i]);
				i++;
			}
		}
	}
	return (ptr);
}
