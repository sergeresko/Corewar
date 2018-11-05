/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 14:45:56 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 14:48:39 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	void	*ptr;

	size++;
	ptr = malloc(size);
	if (ptr)
		ft_bzero(ptr, size);
	return ((char *)ptr);
}
