/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:28:48 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/01 17:01:52 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	_test_bonus(t_vm const *vm)
{
	ft_printf("!@#$ help: %s\n", vm->help ? "TRUE" : "FALSE");
	ft_printf("!@#$ verbose: %s\n", vm->verbose ? "TRUE" : "FALSE");
	ft_printf("!@#$ color: %s\n", vm->color ? "TRUE" : "FALSE");
}

void	_test_dump(t_vm const *vm)
{
	ft_printf("!@#$ dump_cycles: %d\n", vm->dump_cycle);
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

static void		init_vm(t_vm *vm)
{
	vm->help = FALSE;
	vm->verbose = FALSE;
	vm->color = FALSE;
	vm->leaks = FALSE;
	vm->silent = FALSE;
	vm->interactive_cycle = -1;
	vm->dump_cycle = -1;
//	vm->dump_bytes = 32;	// may be left uninitialized
	vm->champ_amount = 0;
	vm->champs = NULL;
}

static void		get_options(t_vm *vm, char **av)
{
	av = get_opt_bonus(vm, av);
	(void)_test_bonus;/////////////////////////////////////
	av = get_opt_dump(vm, av);
	(void)_test_dump;//////////////////////////////////////
	get_opt_champs(vm, av);
	set_champ_ids(vm->champs, vm->champ_amount);
	read_champs(vm->champs);
	(void)_test_champs;////////////////////////////////////
}

int				main(int ac, char **av)
{
	t_vm		vm;

	init_vm(&vm);
	get_options(&vm, av);
	if (ac < 2 || vm.help)
	{
		show_usage(&vm);
	}
	else if (vm.champ_amount == 0)
	{
		fatal_error("No champions");
	}
	else
	{
		perform_battle(&vm);
	}
	if (vm.leaks)
	{
		system("leaks -q corewar >&2");
	}
	return (0);
}
