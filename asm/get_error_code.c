/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 03:59:12 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/02 03:59:12 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_colon(char *eline, t_asm *asm_struct, int i)
{
	int		j;
	char	*colon_line;

	j = 0;
	if (ft_get_substr_index(eline, ":") == 0)
	{
		printf("Syntax error at token [TOKEN][%03d:%03d] "
			   "INDIRECT_LABEL \"%s\"\n", asm_struct->data.line, i + 1, eline);
		exit(-1);
	}
	if (eline[0] == '%')
		check_direct_label(eline, asm_struct, i);
	while (eline[j] != ':')
		++j;
	if (!(colon_line = ft_strnew(j)))
		return ;
	j = 0;
	while (eline[j] != ':')
	{
		colon_line[j] = eline[j];
		++j;
	}
	colon_line[j] = eline[j];
	printf("Syntax error at token [TOKEN][%03d:%03d] LABEL \"%s\"\n",
		   asm_struct->data.line, i + 1, colon_line);
	exit(-1);
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
	{
		printf("Syntax error at token [TOKEN][%03d:%03d] ENDLINE \n",
			   asm_struct->data.line, (int)(ft_strlen(line)) + 1);
		exit(-1);
	}
	else if ((line[i] > 64 && line[i] < 91) || (line[i] > 96 && line[i] < 123)
			 ||	line[i] == 95 || (line[i] > 47 && line[i] < 58) || line[i] == 45)
	{
		if (line[i] == 'r')
			check_register(eline, asm_struct, i);
		if ((line[i] > 47 && line[i] < 58) || line[i] == '-')
			check_indirect(eline, asm_struct, i);
		check_instruction(eline, asm_struct, i);
	}
	else if (line[i] > 47 && line[i] < 58)
	{
		printf("indirect");
		exit(-1);
	}
	else if (line[i] == ',')
	{
		printf("Syntax error at token [TOKEN][%03d:%03d] SEPARATOR \",\" \n",
			   asm_struct->data.line, i + 1);
		exit(-1);
	}
	else if (line[i] == '.')
		check_commands(eline, asm_struct, i);
	else if (line[i] == '%')
		check_direct(eline, asm_struct, i);
	else
		check_lexical(eline, asm_struct, i);
}
