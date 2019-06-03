/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_name_desc_functions.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 03:46:38 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/03 12:38:12 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_instruction(char *eline, t_asm *asm_struct, int i)
{
	ft_printf("Syntax error at token [TOKEN][%03d:%03d] INSTRUCTION \"%s\"\n",
		asm_struct->data.line, i + 1, eline);
	exit(-1);
}

void	check_register(char *eline, t_asm *asm_struct, int i)
{
	int j;

	j = 1;
	if (ft_strlen(eline) > 3 || ft_strlen(eline) == 1)
		check_instruction(eline, asm_struct, i);
	if (eline[j] > 47 && eline[j] < 58 && j < 3)
		++j;
	else
		check_instruction(eline, asm_struct, i);
	ft_printf("Syntax error at token [TOKEN][%03d:%03d] REGISTER \"%s\"\n",
		asm_struct->data.line, i + 1, eline);
	exit(-1);
}

void	check_direct_label(char *eline, t_asm *asm_struct, int i)
{
	ft_printf("Syntax error at token [TOKEN][%03d:%03d] DIRECT_LABEL \"%s\"\n",
		asm_struct->data.line, i + 1, eline);
	exit(-1);
}

int		ft_nbr_lngth(long n)
{
	if (n == 0)
		return (1);
	if (n < 0)
		return (1 + ft_nbr_lngth(n * -1));
	if (n > 0 && n <= 9)
		return (1);
	if (n / 10 != 0)
		return (1 + ft_nbr_lngth(n / 10));
	return (0);
}

void	check_lexical(t_asm *asm_struct, int i)
{
	ft_printf("Lexical error at [%d:%d]\n", asm_struct->data.line, i + 1);
	exit(-1);
}
