/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:28:48 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/28 18:24:04 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	_test_dump(t_vm const *vm)
{
	ft_printf("!@#$ dump_cycles: %d\n", vm->dump_cycles);
	ft_printf("!@#$ dump_bytes: %d\n", vm->dump_bytes);
}

void	_test_champs(t_vm const *vm)
{
	t_list	*champs;
	t_champ	*champ;

	champs = vm->champs;
	while (champs != NULL)
	{
		champ = champs->content;
		ft_printf("!@#$ ----------------\n");
        ft_printf("!@#$ filename: \"%s\"\n", champ->filename);
		ft_printf("!@#$ id: %d\n", champ->id);
		ft_printf("!@#$ size: %d\n", champ->size);
        ft_printf("!@#$ name: \"%s\"\n", champ->name);
        ft_printf("!@#$ comment: \"%s\"\n", champ->comment);
		champs = champs->next;
	}
}

void		init_vm(t_vm *vm)
{
	vm->dump_cycles = -1;
	vm->champ_amount = 0;
	vm->champs = NULL;
}

void		get_options(t_vm *vm, int ac, char **av)
{
	(void)ac;
	av = get_opt_dump(vm, av);
	// <
	_test_dump(vm);
	// >
	get_opt_champs(vm, av);
	set_champ_ids(vm->champs, vm->champ_amount);
	read_champs(vm->champs);
	// <
	_test_champs(vm);
	// >
	if (vm->champ_amount == 0)
	{
		throw_error("No champions");
	}
}

int			main(int ac, char **av)
{
	t_vm	vm;

	init_vm(&vm);
	get_options(&vm, ac, av);

	return (0);
}
