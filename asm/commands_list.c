/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/02/10 15:41:18 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

#define TRUE 1
#define FALSE 0
#define LABEL_SIZE_2 2
#define LABEL_SIZE_4 4
#define COMMAND_MAX_LENGTH 5

t_com	*check_command(char *command);
t_com	*check_command_2(char *command);
t_com	*make_command_struct(char code, int is_codage, int label_size);

t_com	*get_command_from_line(char **tline)
{
	int		i;
	char	*temp;
	char	*command;

	if (!(*tline) || !ft_islower(**tline))
		return (NULL);		// add error handling
	i = 0;
	if (!(command = ft_strnew(sizeof(char) * COMMAND_MAX_LENGTH)))
		perror("Allocation error!");		// add error handling
	while (ft_islower((*tline)[i]))
	{
		if (i == COMMAND_MAX_LENGTH)
			return (NULL);		// add error handling
		command[i] = (*tline)[i];
		i++;
	}
	temp = ft_strtrim(ft_strsub(*tline, (unsigned int)i, ft_strlen(*tline) - i));
	ft_strdel(tline);
	tline = &temp;
	return check_command(command);
}

t_com	*check_command(char *command)
{
	if (ft_strequ("live", command))
		return (make_command_struct(1, FALSE, LABEL_SIZE_4));
	else if (ft_strequ("ld", command))
		return (make_command_struct(2, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("st", command))
		return (make_command_struct(3, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("add", command))
		return (make_command_struct(4, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("sub", command))
		return (make_command_struct(5, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("and", command))
		return (make_command_struct(6, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("or", command))
		return (make_command_struct(7, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("xor", command))
		return (make_command_struct(8, TRUE, LABEL_SIZE_4));
	else if (ft_strequ("zjmp", command))
		return (make_command_struct(9, FALSE, LABEL_SIZE_2));
	else
		return check_command_2(command);
}

t_com	*check_command_2(char *command)
{
	if (ft_strequ("ldi", command))
		return (make_command_struct(10, FALSE, LABEL_SIZE_2));
	if (ft_strequ("sti", command))
		return (make_command_struct(11, TRUE, LABEL_SIZE_2));
	if (ft_strequ("fork", command))
		return (make_command_struct(12, FALSE, LABEL_SIZE_2));
	if (ft_strequ("lld", command))
		return (make_command_struct(13, TRUE, LABEL_SIZE_4));
	if (ft_strequ("lldi", command))
		return (make_command_struct(14, TRUE, LABEL_SIZE_2));
	if (ft_strequ("lfork", command))
		return (make_command_struct(15, FALSE, LABEL_SIZE_2));
	if (ft_strequ("aff", command))
		return (make_command_struct(16, TRUE, LABEL_SIZE_4));
	else
		return (NULL);
}

t_com	*make_command_struct(char code, int is_codage, int label_size)
{
	t_com	*new_command_struct;

	if ((new_command_struct = ft_memalloc(sizeof(t_com))))
	{
		new_command_struct->code = code;
		new_command_struct->is_codage = is_codage;
		new_command_struct->label_size = label_size;
		return (new_command_struct);
	}
	return (NULL);
}
