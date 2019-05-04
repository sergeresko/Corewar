/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/02/10 15:07:27 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	e__args_amount(void)
{
	ft_putendl(ASM_USAGE);
	exit(-1);
}

void	e__asm_initialization(void)
{
	ft_putendl(ASM_INITIALIZATION_ERROR);
	exit(-1);
}

void	e__open_file(const char *name)
{
	ft_putstr(OPEN_FILE_ERROR);
	ft_printf("'%s'\n", name);
	exit(-1);
}

void	e__read_file(void)
{
	ft_putendl(READ_FILE_ERROR);
	exit(-1);
}

void	e__trim_line(const char *line)
{
	ft_putstr(TRIM_LINE_ERROR);
	ft_printf("'%s'\n", line);
	exit(-1);
}
