/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <syeresko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:40:58 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/19 19:17:44 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		is_valid_op_code(char c)		// t_bool
{
	return (1 <= c && c <= 16);
}

void	perform_process(t_vm *vm, t_process *p)
{
	if (p->delay == 0)				// i.e. if `p->pc` is at a new position
	{
		p->op_code = vm->arena[p->pc];
		if (!is_valid_op_code(p->op_code))
		{
			p->pc = (p->pc + 1) % MEM_SIZE;		// advance `p->pc` by 1 byte
			return ;
		}
		p->delay = vm->op[p->op_code].delay;
	}
	--(p->delay);
	if (p->delay == 0)
	{
		execute_operation(vm, p);		// <----------
	}
}

/*
**	`perform_cycle` calls `perform_process` for each process
*/

void	perform_cycle(t_vm *vm)
{
	t_list		*item;

	++(vm->cycle);				// increment
	item = vm->processes;
	while (item != NULL)
	{
		perform_process(vm, item->data);
		item = item->next;
	}
}

/*
**	`perform_check` kills all processes that haven't executed `live` since the
**	previous check
*/

void	perform_check(t_vm *vm)
{
	int const	oldest_cycle = vm->cycle - vm->cycles_to_die;
	t_list		**addr;
	t_process	*p;

	++(vm->nbr_checks);			// increment
	*addr = &(vm->processes);
	while (*addr != NULL)
	{
		p = (*addr)->data;
		if (p->cycle_when_last_live <= oldest_cycle)
		{
			list_pop(addr);		// delete process `p`
		}
		else
		{
			addr = &(*addr)->next;
		}
	}
}

/*
**	`perform_round` calls `perform_cycle` the necessary number of times
**	and then calls `perform_check` once
*/

// used in `perform_round`
static int	compute_last_cycle(t_vm const *vm)
{
	return (vm->cycle + ((vm->cycles_to_die > 0) ? vm->cycles_to_die : 1));
}

void	perform_round(t_vm *vm)
{
	int const	last_cycle = compute_last_cycle(vm);

	// ...
	vm->nbr_live = 0;
	while (vm->cycle < last_cycle /* ... */)
	{
		perform_cycle(vm);
	}
	perform_check(vm);
	if (vm->nbr_live >= NBR_LIVE || vm->nbr_checks == MAX_CHECKS)
	{
		vm->cycles_to_die -= CYCLE_DELTA;
		vm->nbr_checks = 0;
	}
}

// ----------------

void	load_players(t_vm *vm)
{
	int const	step = MEM_SIZE / vm->nbr_players;
	int			i;

	i = 0;
	ft_bzero(vm->arena, MEM_SIZE);
	while (i < vm->nbr_players)
	{
		// ...
		ft_memcpy(vm->arena + step * i, vm->players[i]->code, vm->players[i]->size);
		++i;
	}
}

void	init_processes(t_vm *vm)
{

}

/*
**	`perform_battle` calls `perform_round` while there are living processes
*/

void	perform_battle(t_vm *vm)
{
	vm->cycle = 0;							// init
	vm->cycles_to_die = CYCLE_TO_DIE;		// init
	vm->nbr_checks = 0;						// init
	// ...
	while (vm->processes != NULL /* ... */)
	{
		perform_round(vm);
	}
	// ...
}
