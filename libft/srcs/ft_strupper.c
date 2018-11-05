/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:09:51 by vlvereta          #+#    #+#             */
/*   Updated: 2018/06/11 13:36:48 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strupper(char *s)
{
	int		i;
	char	*result;

	result = NULL;
	if (s && (result = ft_strdup(s)))
	{
		i = 0;
		while (result[i])
		{
			result[i] = ft_toupper(result[i]);
			i++;
		}
	}
	return (result);
}
