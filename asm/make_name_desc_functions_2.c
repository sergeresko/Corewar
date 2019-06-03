/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_name_desc_functions_2.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 03:52:00 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/03 14:06:50 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_commands(char *eline, t_asm *asm_struct, int i)
{
	if (ft_get_substr_index(eline, NAME_CMD_STRING) == 0)
	{
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] "
			"COMMAND_NAME \".name\"\n", asm_struct->data.line, i + 1);
		exit(-1);
	}
	if (ft_get_substr_index(eline, COMMENT_CMD_STRING) == 0)
	{
		ft_printf("Syntax error at token [TOKEN][%03d:%03d] "
			"COMMAND_COMMENT \".comment\"\n", asm_struct->data.line, i + 1);
		exit(-1);
	}
	check_lexical(asm_struct, i);
}

int		check_for_letters(char *eline)
{
	size_t	j;

	j = 0;
	while (j < ft_strlen(eline))
	{
		if (!(eline[j] > 47 && eline[j] < 58))
			return (1);
		++j;
	}
	return (0);
}

void	check_for_symbols(char *eline, t_asm *asm_struct, int i)
{
	size_t	j;

	j = 0;
	while (j < ft_strlen(eline))
	{
		if (!(eline[j] > 47 && eline[j] < 58) && !(eline[j] > 64 &&
			eline[j] < 91) && !(eline[j] > 96 && eline[j] < 123))
			check_lexical(asm_struct, i + j + 1);
		++j;
	}
}

void	check_indirect(char *eline, t_asm *asm_struct, int i)
{
	if (eline[0] == '-' && !(eline[1] > 47 && eline[1] < 58))
		check_lexical(asm_struct, i);
	if (eline[1] == ':')
		check_direct_label(eline, asm_struct, i);
	check_for_symbols(eline, asm_struct, i);
	if (check_for_letters(eline))
		check_instruction(eline, asm_struct, i);
	ft_printf("Syntax error at token [TOKEN][%03d:%03d] INDIRECT \"%s\"\n",
		asm_struct->data.line, i + 1, eline);
	exit(-1);
}

void	check_direct(char *eline, t_asm *asm_struct, int i)
{
	char	*direct_line;
	int		j;
	int		k;

	j = 1;
	k = 0;
	if (!(eline[1] > 47 && eline[1] < 58))
		check_lexical(asm_struct, i);
	if (eline[1] == ':')
		check_direct_label(eline, asm_struct, i);
	while (eline[j] > 47 && eline[j] < 58)
		++j;
	if (!(direct_line = ft_strnew(j)))
		return ;
	while (k < j)
	{
		direct_line[k] = eline[k];
		++k;
	}
	ft_printf("DIRECT \"%s\"", direct_line);
	exit(-1);
}
