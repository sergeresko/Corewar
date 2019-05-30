/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <syeresko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:40:58 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/30 15:30:51 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	returns TRUE or FALSE
*/

int		is_valid_opcode(int code)
{
	return (1 <= code && code <= 16);
}

void	execute_car(t_vm *vm, t_car *car)
{
	if (car->delay == 0)		// i.e. if `car->place` is at a new position
	{
		car->opcode = vm->field[car->place].square;		// equivalent to `= read_from_field(vm->field, car->place, 1)`
		if (!is_valid_opcode(car->opcode))
		{
			car->place = (car->place + 1) % MEM_SIZE;	// advance `car->place` by 1 byte
			return ;
		}
		car->delay = g_ops[car->opcode].delay;
	}
	--(car->delay);
	if (car->delay == 0)
	{
//		ft_printf("executing operation at 0x%04x\n", car->place);		////////////////////
/*
		if (car->opcode == 1)										//
		{															//
			ft_printf("Call to `live`, skipping\n");				//
			car->place = (car->place + car->offset) % MEM_SIZE;		//
			return ;												//
		}															//
*/
		execute_operation(vm, car);
	}
}

/*
**	`perform_cycle` calls `execute_car` for each car
*/

void	perform_cycle(t_vm *vm)
{
	t_list		*item;

	++(vm->cycle);				// increment
	if (vm->verbose)
	{
		ft_printf("It is now cycle %d\n", vm->cycle);
	}
	item = vm->cars;
	while (item != NULL)
	{
		execute_car(vm, item->content);
		item = item->next;
	}
}

/*
**	`perform_check` kills all cars that haven't executed `live` since
**	the previous check
*/

void	perform_check(t_vm *vm)
{
	int const	oldest_cycle = vm->cycle - vm->cycle_to_die;
	t_list		**addr;
	t_car		*car;

	++(vm->nbr_checks);			// increment
	addr = &(vm->cars);
	while (*addr != NULL)
	{
		car = (*addr)->content;
		if (car->cycle_when_last_live <= oldest_cycle)
		{
			free(list_pop(addr));	// delete car `car`
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
	return (vm->cycle + ((vm->cycle_to_die > 0) ? vm->cycle_to_die : 1));
}

void	perform_round(t_vm *vm)
{
	int const	last_cycle = compute_last_cycle(vm);

	vm->nbr_live = 0;
	while (vm->cycle < last_cycle)
	{
		if (vm->cycle == vm->dump_cycle)
		{
			return ;
		}
		perform_cycle(vm);
	}
	perform_check(vm);
	if (vm->nbr_live >= NBR_LIVE || vm->nbr_checks == MAX_CHECKS)
	{
		vm->cycle_to_die -= CYCLE_DELTA;
		vm->nbr_checks = 0;
		if (vm->verbose)
		{
			ft_printf("Cycle to die is now %d\n", vm->cycle_to_die);
		}
	}
}

// ----------------
void		dump_memory(t_vm const *vm)
{
	int		start;
	int		k;

	start = 0;
	k = 0;
	while (start < MEM_SIZE)
	{
		ft_printf("0x%04x : ", start);
		start += vm->dump_bytes;
		while (k < start)
		{
			ft_printf("%02hhx ", vm->field[k].square);
			++k;
		}
		ft_putchar('\n');
	}
}
// ----------------

void	clear_field(t_field *field)
{
	int		k;

	k = 0;
	while (k < MEM_SIZE)
	{
		field[k].square = 0;	// only .square
		++k;
	}
}

void	load_exec_code(t_field *field, int place, char *exec_code, int size)
{
	t_field *const	origin = field + place;
	int				k;

	k = 0;
	while (k < size)
	{
		origin[k].square = exec_code[k];
		++k;
	}
}

void	load_champs(t_vm *vm)
{
	int const	step = MEM_SIZE / vm->champ_amount;
	int			champ_id;
	t_champ		*champ;
	t_car		*car;

	clear_field(vm->field);		// init
	vm->cars = NULL;			// init
	champ_id = 1;
	while (champ_id <= vm->champ_amount)
	{
		champ = get_champ_by_id(vm->champs, champ_id);
		load_exec_code(vm->field, step * (champ_id - 1),
				champ->exec_code, champ->size);
		car = create_car();
		car->regs[1] = -champ_id;		// TODO: ?
		car->place = step * (champ_id - 1);
		// initialize other fields of `car` ?
		list_push(&(vm->cars), car);
		++champ_id;
	}
}

/*
**	`perform_battle` calls `perform_round` while there are living processes
*/

void	perform_battle(t_vm *vm)
{
	vm->cycle = 0;							// init
	vm->cycle_to_die = CYCLE_TO_DIE;		// init
	vm->nbr_checks = 0;						// init
	// ...
	load_champs(vm);
//	ft_printf("%p\n", vm->cars);//////////////////
	while (vm->cars != NULL && vm->cycle != vm->dump_cycle)
	{
		perform_round(vm);
	}
	if (vm->cars == NULL && vm->last_living_champ_id != 0)
	{
		ft_printf("Player %d (%s) won\n", vm->last_living_champ_id, get_champ_by_id(vm->champs, vm->last_living_champ_id)->name);	// TODO: to a separate function
	}
	if (vm->cycle == vm->dump_cycle)
	{
		dump_memory(vm);
	}
	// ...

}
