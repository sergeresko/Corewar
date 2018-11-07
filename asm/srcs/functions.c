/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/11/05 20:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*check_comment(char **line)
{
	if (**line == '#')
	{
		ft_strdel(line);
		return (NULL);
	}
	return (*line);
}

void	clean_and_exit(void **ptr)
{
	if (*ptr)
		ft_memdel(ptr);
	exit(0);
}