/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/11/08 20:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int g_error_mode = FALSE;
const t_arg_type LIVE[3][3] = {{T_DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}};
const t_arg_type LD[3][3] = {{T_DIR, T_IND, 0}, {T_REG, 0, 0}, {0, 0, 0}};
const t_arg_type ST[3][3] = {{T_REG, 0, 0}, {T_REG, T_IND, 0}, {0, 0, 0}};
const t_arg_type ADD[3][3] = {{T_REG, 0, 0}, {T_REG, 0, 0}, {T_REG, 0, 0}};
const t_arg_type SUB[3][3] = {{T_REG, 0, 0}, {T_REG, 0, 0}, {T_REG, 0, 0}};
const t_arg_type AND[3][3] = {{T_REG, T_DIR, T_IND}, {T_REG, T_DIR, T_IND}, {T_REG, 0, 0}};
const t_arg_type OR[3][3] = {{T_REG, T_DIR, T_IND}, {T_REG, T_DIR, T_IND}, {T_REG, 0, 0}};
const t_arg_type XOR[3][3] = {{T_REG, T_DIR, T_IND}, {T_REG, T_DIR, T_IND}, {T_REG, 0, 0}};
const t_arg_type ZJMP[3][3] = {{T_DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}};
const t_arg_type LDI[3][3] = {{T_REG, T_DIR, T_IND}, {T_REG, T_DIR, 0}, {T_REG, 0, 0}};
const t_arg_type STI[3][3] = {{T_REG, 0, 0}, {T_REG, T_DIR, T_IND}, {T_REG, T_DIR, 0}};
const t_arg_type FORK[3][3] = {{T_DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}};
const t_arg_type LLD[3][3] = {{T_DIR, T_IND, 0}, {T_REG, 0, 0}, {0, 0, 0}};
const t_arg_type LLDI[3][3] = {{T_REG, T_DIR, T_IND}, {T_REG, T_DIR, 0}, {T_REG, 0, 0}};
const t_arg_type LFORK[3][3] = {{T_DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}};
const t_arg_type AFF[3][3] = {{T_REG, 0, 0}, {0, 0, 0}, {0, 0, 0}};

int		asm_init(t_asm **asm_struct, const char *argv)
{
	if (!(*asm_struct = ft_memalloc(sizeof(t_asm))))
	{
		perror(ALLOCATION_ERROR);
		return (0);
	}
	if (!((*asm_struct)->filename = get_filename(argv)))
	{
		clean_asm_struct(asm_struct);
		return (0);
	}
//	(*asm_struct)->counter = MAX_COUNTER;
	return (1);
}

char	*get_filename(const char *argv)
{
	int	start;
	int	len;

	len = ft_strlen(argv);
	if (len <= 2 || argv[len - 1] != 's' || argv[len - 2] != '.')
		return (NULL);
	start = len - 1;
	while (start >= 0 && argv[start] != ' ' && argv[start] != '/')
		start--;
	start++;
	return (ft_strsub(argv, start, len - start - 2));
}

void	clean_asm_struct(t_asm **asm_struct)
{
	if ((*asm_struct)->filename)
		ft_memdel((void **)&((*asm_struct)->filename));
	if ((*asm_struct)->labels)
		clean_labels_list(&((*asm_struct)->labels));
	if ((*asm_struct)->commands)
		clean_commands_list(&((*asm_struct)->commands));
	ft_memdel((void **)asm_struct);
}

void	clean_labels_list(t_label **labels)
{
	if (labels && *labels)
	{
		ft_strdel(&((*labels)->name));
		if ((*labels)->next)
			clean_labels_list(&((*labels)->next));
		ft_memdel((void **)labels);
	}
}

void	clean_commands_list(t_com **commands)
{
	if (commands && *commands)
	{
		if ((*commands)->next)
			clean_commands_list(&((*commands)->next));
		ft_strdel(&((*commands)->name));
		if ((*commands)->arg_labels[0])
			ft_strdel(&((*commands)->arg_labels[0]));
		if ((*commands)->arg_labels[1])
			ft_strdel(&((*commands)->arg_labels[1]));
		if ((*commands)->arg_labels[2])
			ft_strdel(&((*commands)->arg_labels[2]));
		ft_memdel((void **)commands);
	}
}

int 	get_argument_number(t_com *command)
{
	if (!command->arg_types[0])
		return (0);
	if (!command->arg_types[1])
		return (1);
	if (!command->arg_types[2])
		return (2);
	return (-1);
}

int 	check_argument_1(char *command, int arg_num, t_arg_type arg_type)
{
	if (ft_strequ(command, "live"))
		return (is_argument_possible(LIVE[arg_num], arg_type));
	else if (ft_strequ(command, "ld"))
		return (is_argument_possible(LD[arg_num], arg_type));
	else if (ft_strequ(command, "st"))
		return (is_argument_possible(ST[arg_num], arg_type));
	else if (ft_strequ(command, "add"))
		return (is_argument_possible(ADD[arg_num], arg_type));
	else if (ft_strequ(command, "sub"))
		return (is_argument_possible(SUB[arg_num], arg_type));
	else if (ft_strequ(command, "and"))
		return (is_argument_possible(AND[arg_num], arg_type));
	else if (ft_strequ(command, "or"))
		return (is_argument_possible(OR[arg_num], arg_type));
	else if (ft_strequ(command, "xor"))
		return (is_argument_possible(XOR[arg_num], arg_type));
	else if (ft_strequ(command, "zjmp"))
		return (is_argument_possible(ZJMP[arg_num], arg_type));
	else if (ft_strequ(command, "ldi"))
		return (is_argument_possible(LDI[arg_num], arg_type));
	else
		return check_argument_2(command, arg_num, arg_type);
}

int 	check_argument_2(char *command, int arg_num, t_arg_type arg_type)
{
	if (ft_strequ(command, "sti"))
		return (is_argument_possible(STI[arg_num], arg_type));
	else if (ft_strequ(command, "fork"))
		return (is_argument_possible(FORK[arg_num], arg_type));
	else if (ft_strequ(command, "lld"))
		return (is_argument_possible(LLD[arg_num], arg_type));
	else if (ft_strequ(command, "lldi"))
		return (is_argument_possible(LLDI[arg_num], arg_type));
	else if (ft_strequ(command, "lfork"))
		return (is_argument_possible(LFORK[arg_num], arg_type));
	else if (ft_strequ(command, "aff"))
		return (is_argument_possible(AFF[arg_num], arg_type));
	else
	{
		ft_printf("Unknown command %s! Exiting..\n", command);
		exit(-1);
	}
}

int 	is_argument_possible(const t_arg_type arg_types[], t_arg_type arg_type)
{
	int 	i;

	i = 0;
	if (!arg_types[0] && !arg_types[1] && !arg_types[2])
		return (-1);
	while (i < 3)
	{
		if (arg_types[i] == arg_type)
			return (TRUE);
		i++;
	}
	return (FALSE);
}