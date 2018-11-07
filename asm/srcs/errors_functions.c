/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/09/30 20:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	e__no_args(void)
{
	ft_putendl(NO_ARGS_ERROR);
	exit(-1);
}

void	e__read_file(int fd)
{
	perror(READ_FILE_ERROR);
	close(fd);
	exit(-1);
}

void	e__open_file(const char *name)
{
	ft_printf("Can't read source file %s\n", name);
	exit(-1);
}