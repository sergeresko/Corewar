/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 14:18:12 by vlvereta          #+#    #+#             */
/*   Updated: 2018/02/05 16:09:24 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		start_initialization(t_info *p)
{
	ft_bzero(p, sizeof(t_info));
	if (!(p->cur_flags = (t_flags *)malloc(sizeof(t_flags))))
		return (0);
	flags_to_null(p->cur_flags);
	if (!(p->output = (char *)malloc(sizeof(char))))
		return (clean_return(p->cur_flags, 0, 0, 0));
	*(p->output) = '\0';
	p->types = "cCdDinoOpsSuUxX%";
	type_handlers_init(p->type_handlers);
	return (1);
}

void	type_handlers_init(t_handler type_handlers[])
{
	type_handlers[0] = &type_low_c;
	type_handlers[1] = &type_high_c;
	type_handlers[2] = &type_low_di;
	type_handlers[3] = &type_high_d;
	type_handlers[4] = &type_low_di;
	type_handlers[5] = &type_n;
	type_handlers[6] = &type_low_o;
	type_handlers[7] = &type_high_o;
	type_handlers[8] = &type_p;
	type_handlers[9] = &type_low_s;
	type_handlers[10] = &type_high_s;
	type_handlers[11] = &type_low_u;
	type_handlers[12] = &type_high_u;
	type_handlers[13] = &type_low_x;
	type_handlers[14] = &type_high_x;
	type_handlers[15] = &percent_handling;
}

void	flags_to_null(t_flags *flags)
{
	ft_bzero(flags, sizeof(t_flags));
	flags->prec = -1;
}
