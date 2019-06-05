/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_direct_label.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 02:23:55 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/04 00:45:52 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	direct_label_syntax_label(char *label)
{
	ft_printf("Syntax error, direct_label \"%%:%s\"\n", label);
	exit(-1);
}

void	direct_label_argument(int arg_num)
{
	ft_printf("Argument number - %d\n", arg_num);
	exit(-1);
}

void	direct_label_syntax(char *label)
{
	ft_printf("Syntax error, direct \"%%:%s\"\n", label);
	exit(-1);
}

int		read_direct_label(char **tline, int i, t_com *command)
{
	int		j;
	int		arg_num;
	int		checked;
	char	*label;

	if ((j = check_label(*tline, ++i, FALSE)))
	{
		label = ft_strsub(*tline, i, j - i);
		if (g_error_mode || !command)
			direct_label_syntax_label(label);
		if ((arg_num = get_arg_num(command)) == -1)
			direct_label_argument(arg_num);
		if ((checked = check_arg_1(command->name, arg_num, T_DIR)) == -1)
			direct_label_syntax(label);
		if (!checked)
		{
			ft_printf("Invalid parameter %d type direct for instruction %s\n",
					arg_num, command->name);
			exit(-1);
		}
		write_l_a(command, arg_num, T_DIR, &label);
		return (check_proper_ending(*tline, j));
	}
	return (i);
}
