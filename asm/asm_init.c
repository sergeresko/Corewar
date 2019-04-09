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
		ft_memdel((void **)commands);
	}
}