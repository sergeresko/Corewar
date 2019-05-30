/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/31 02:30:11 by ozalisky         ###   ########.fr       */
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

void		e__read_file(t_asm *asm_struct, int error_case)
{
	switch (error_case) {
		case 1: ft_printf("Syntax error at token [TOKEN][%03d:%03d] ENDLINE\n",
						  asm_struct->data.line, asm_struct->data.row + 1);
			break;
		case 2: ft_printf("Lexical error at [%d:%d]\n",
						  asm_struct->data.line, 1);
			break;
		case 3: ft_printf("Syntax error at token [TOKEN][%03d:%03d] INSTRUCTION"
						  " %s\n",
						  asm_struct->data.line, asm_struct->data.row + 1);
			break;
		case 4: ft_printf("Syntax error at token [TOKEN][%03d:%03d] LABEL "
						  "%s\n",
						  asm_struct->data.line, asm_struct->data.row + 1);
			break;
		case 5: ft_printf("Syntax error - unexpected end of input (Perhaps you "
						  "forgot to end with a newline ?)");
			exit(-1);
		case 6: ft_putendl(READ_FILE_ERROR);
			exit(-1);
	}
}

void	e__trim_line(const char *line)
{
	ft_putstr(TRIM_LINE_ERROR);
	ft_printf("'%s'\n", line);
	exit(-1);
}
