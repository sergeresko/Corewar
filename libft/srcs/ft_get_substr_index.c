/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_substr_index.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:36:30 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/28 20:36:57 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_get_substr_index(const char *big, const char *little)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	if (!(*little))
		return (0);
	while (big[i])
	{
		j = 0;
		k = i;
		while (big[i] && little[j] && big[i] == little[j])
		{
			if (!little[++j])
				return (k);
			i++;
		}
		i = ++k;
	}
	return (-1);
}
