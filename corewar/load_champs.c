/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 17:09:30 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/01 22:06:34 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void		clear_field(t_field *field)
{
	int			k;

	k = 0;
	while (k < MEM_SIZE)
	{
		field[k].square = 0;
		field[k].champ_id = 0;
		++k;
	}
}

static void		load_exec_code(t_field *field, int place, t_champ const *champ)
{
	int			k;

	field += place;
	k = 0;
	while (k < champ->size)
	{
		field[k].square = champ->exec_code[k];
		field[k].champ_id = champ->id;
		++k;
	}
}

static void		push_champ_first_car(t_vm *vm, int champ_id, int place)
{
	t_car		*car;

	car = create_car();
	car->champ_id = champ_id;
	car->regs[1] = -champ_id;
	car->place = place;
	list_push(&vm->cars, car);
}

#define FMT		"* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n"
#define FMT_COL	PF_BOLD FMT PF_RESET

void			load_champs(t_vm *vm)
{
	int const	step = MEM_SIZE / vm->champ_amount;
	int			champ_id;
	t_champ		*champ;

	clear_field(vm->field);
	ft_putstr("Introducing contestants...\n");
	champ_id = 1;
	while (champ_id <= vm->champ_amount)
	{
		champ = get_champ_by_id(vm->champs, champ_id);
		if (vm->opt.color)
		{
			ft_putstr(g_champ_colors[champ_id]);
		}
		ft_printf(vm->opt.color ? FMT_COL : FMT,
				champ->id, champ->size, champ->name, champ->comment);
		load_exec_code(vm->field, step * (champ_id - 1), champ);
		push_champ_first_car(vm, champ_id, step * (champ_id - 1));
		++champ_id;
	}
}
