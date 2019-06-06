/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 03:59:12 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/03 12:36:58 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	syntax_error(t_asm *asm_struct, char *line)
{
	ft_printf("Syntax error at token [TOKEN][%03d:%03d] ENDLINE \n",
		asm_struct->data.line, (int)(ft_strlen(line)) + 1);
	exit(-1);
}

void	separator_error(t_asm *asm_struct, int i)
{
	ft_printf("Syntax error at token [TOKEN][%03d:%03d] SEPARATOR \",\" \n",
		asm_struct->data.line, i + 1);
	exit(-1);
}

void	indirect_error(t_asm *asm_struct, int i)
{
	ft_printf("Syntax error at token [TOKEN][%03d:%03d] INDIRECT \",\" \n",
		asm_struct->data.line, i + 1);
	exit(-1);
}

void	get_error_code_2(char *line, t_asm *asm_struct, int i, char *eline)
{
	if ((line[i] > 64 && line[i] < 91) || (line[i] > 96 && line[i] < 123)
		|| line[i] == 95 || (line[i] > 47 && line[i] < 58) || line[i] == 45)
	{
		if (line[i] == 'r')
			check_register(eline, asm_struct, i);
		if ((line[i] > 47 && line[i] < 58) || line[i] == '-')
			check_indirect(eline, asm_struct, i);
		check_instruction(eline, asm_struct, i);
	}
	else if (line[i] > 47 && line[i] < 58)
		indirect_error(asm_struct, i);
	else if (line[i] == ',')
		separator_error(asm_struct, i);
	else if (line[i] == '.')
		check_commands(eline, asm_struct, i);
	else if (line[i] == '%')
		check_direct(eline, asm_struct, i);
	else
		check_lexical(asm_struct, i);
}

void	get_error_code(char *line, t_asm *asm_struct, int i)
{
	char	*eline;
	int		j;
	int		eline_index;

	j = i;
	eline_index = 0;
	while (line[j] != ' ' && line[j] != '\0' && line[j] != '"')
		++j;
	if (!(eline = ft_strnew(j - i)))
		return ;
	j = i;
	while (line[j] != ' ' && line[j] != '\0' && line[j] != '"')
		eline[eline_index++] = line[j++];
	if (ft_get_substr_index(eline, ":") >= 0)
		check_colon(eline, asm_struct, i);
	if (line[i] == 35 || line[i] == '\0')
		syntax_error(asm_struct, line);
	get_error_code_2(line, asm_struct, i, eline);
}
