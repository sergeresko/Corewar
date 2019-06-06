/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_name_and_desc_error.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 12:51:25 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/05 12:52:15 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	long_name_error(void)
{
	ft_printf("Champion name too long (Max length 128)\n");
	exit(-1);
}

void	long_desc_error(void)
{
	ft_printf("Champion comment too long (Max length 2048)");
	exit(-1);
}
