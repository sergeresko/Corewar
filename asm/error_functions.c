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
	ft_putendl(USAGE);
	exit(-1);
}

void	e__open_file(const char *name)
{
	ft_printf("Can't read source file %s\n", name);
	exit(-1);
}

void	e__read_file(t_asm *asm_struct, int errorCase)
{
	switch (errorCase) {
		case 1: ft_printf("Syntax error at token [TOKEN][%03d:%03d] ENDLINE\n",
						  asm_struct->data.line, asm_struct->data.row + 1);
			break;
		default: ft_printf("Default\n", asm_struct->data.line,
				asm_struct->data.row);
	}

	exit(-1);
}