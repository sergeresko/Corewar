/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 15:24:41 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/30 12:19:21 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	t;

	i = 0;
	if (!little[i])
		return ((char *)big);
	while (big[i])
	{
		j = 0;
		t = i;
		while (big[i] && little[j] && big[i] == little[j])
		{
			if (!little[++j])
				return ((char *)big + t);
			i++;
		}
		i = t + 1;
	}
	return (NULL);
}
