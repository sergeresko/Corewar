/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dump_output.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 18:27:04 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/04 19:09:56 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_add_com_line_1(t_com *com, int line, t_asm *ast_str)
{
	int		i;
	char	*temp;
	int		label_index;
	int		label_arg;

	i = -1;
	ft_printf("                    ");
	temp = ft_itoa(com->code);
	print_in_length(4, &temp);
	temp = com->is_codage ? ft_itoa(com->codage) : NULL;
	print_in_length(6, &temp);
	while (++i < 3)
	{
		if (com->arg_labels[i])
		{
			label_index = get_label_index(ast_str->labels, com->arg_labels[i]);
			label_arg = label_index - com->index;
		}
		else
			label_arg = com->arguments[i];
		if (!print_add_com_line_2(com, i, line, label_arg))
			continue ;
	}
	ft_putchar('\n');
}

int		print_add_com_line_2(t_com *com, int i, int l, int l_arg)
{
	char	*temp;

	if (com->arg_types[i] == T_REG)
	{
		temp = ft_itoa((unsigned char)l_arg);
		print_in_length(18, &temp);
		return (0);
	}
	else if (com->arg_types[i] == T_IND)
	{
		if (l == 2)
		{
			temp = ft_itoa(l_arg);
			print_in_length(18, &temp);
			return (0);
		}
		print_by_bytes(l_arg, 2);
		ft_putstr("          ");
	}
	else if (com->arg_types[i] == T_DIR)
		return (print_add_com_line_3(com, l, l_arg));
	return (1);
}

int		print_add_com_line_3(t_com *com, int line, int label_arg)
{
	char	*temp;

	if (line == 2)
	{
		temp = ft_itoa(label_arg);
		print_in_length(18, &temp);
		return (0);
	}
	print_by_bytes(label_arg, com->label_size);
	if (com->label_size == 2)
		ft_putstr("          ");
	else
		ft_putstr("  ");
	return (1);
}

void	print_by_bytes(int arg, int bytes)
{
	int				i;
	char			*t;
	unsigned char	temp;

	i = 0;
	while (i < bytes)
	{
		temp = arg >> (bytes - ++i) * BYTE;
		t = ft_itoa(temp);
		print_in_length(4, &t);
	}
}

void	print_in_length(int length, char **str)
{
	int i;
	int len;

	if (str)
	{
		i = 0;
		len = (int)ft_strlen(*str);
		while (i < length)
		{
			if (i < len)
			{
				ft_printf("%c", (*str)[i++]);
				continue;
			}
			ft_putchar(' ');
			i++;
		}
		ft_strdel(str);
		return ;
	}
	perror("Print in length");
	exit(-1);
}
