/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:28:48 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/28 16:46:20 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	get_opt_champs(vm, av);
	set_champ_ids(vm->champs);
	read_champs(vm->champs);
}

void	_test(t_vm const *vm)
{
	t_list	*champs;
	t_champ	*champ;

	ft_printf("Test output!   < - - -\n");
	ft_printf("dump_cycles: %d\n", vm->dump_cycles);
	ft_printf("dump_bytes: %d\n", vm->dump_bytes);
	champs = vm->champs;
	while (champs != NULL)
	{
		champ = champs->content;
		ft_printf("id: %d\n", champ->id);
        ft_printf("name: \"%s\"\n", champ->name);
		ft_printf("size: %d\n", champ->size);
        ft_printf("comment: \"%s\"\n", champ->comment);
        ft_printf("filename: \"%s\"\n", champ->filename);
		champs = champs->next;
	}
	ft_printf("End of test output!   - - - >\n");
}

int			main(int ac, char **av)
{
	t_vm	vm;

	init_vm(&vm);
	get_options(&vm, ac, av);

	_test(&vm);

	return (0);
}
