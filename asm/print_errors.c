/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 17:36:32 by ozalisky          #+#    #+#             */
/*   Updated: 2019/06/03 16:35:26 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	print_label_error(t_com *com, int a_n)
{
	ft_printf("No such label %s while attempting to dereference "
			"token %s \"%c%s\"\n", com->arg_labels[a_n],
			com->arg_types[a_n] == T_DIR ? "DIRECT_LABEL" : "INDIRECT_LABEL",
			com->arg_types[a_n] == T_DIR ? '%' : ':', com->arg_labels[a_n]);
}
