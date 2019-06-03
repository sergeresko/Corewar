/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_reg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 12:05:42 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/29 12:55:33 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

unsigned char	get_reg(t_vm const *vm, t_car const *car, int arg)
{
	return (read_from_field(vm->field, car->arg_place[arg], 1));
}
