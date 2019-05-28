/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <syeresko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 16:40:58 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/23 17:55:23 by syeresko         ###   ########.fr       */
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
		car->opcode = vm->field[car->place].square;		// use `read_from_field`
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
	item = vm->cars;
	while (item != NULL)
	{
		perform_process(vm, item->content);
		item = item->next;
	}
}

/*
**	`perform_check` kills all cars that haven't executed `live` since
**	the previous check
*/

void	perform_check(t_vm *vm)
{
	int const	oldest_cycle = vm->cycle - vm->cycles_to_die;
	t_list		**addr;
	t_car		*car;

	++(vm->nbr_checks);			// increment
	addr = &(vm->cars);
	while (*addr != NULL)
	{
		car = (*addr)->content;
		if (car->cycle_when_last_live <= oldest_cycle)
		{
			list_pop(addr);		// delete car `car`		// free ?
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

static void	print_hex(unsigned char byte)
{
	char	str[2];

	str[0] = (char)(byte / 16);
	str[0] += (str[0] < 10) ? '0' : ('a' - 10);
	str[1] = (char)(byte % 16);
	str[1] += (str[1] < 10) ? '0' : ('a' - 10);
	write(1, str, 2);
}

void		dump_memory(t_field const *field)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		print_hex(field[i].square);
		if (i % 2)
		{
			ft_putchar((i + 1) % 32 ? ' ' : '\n');
		}
		++i;
	}
}

// ----------------

static t_champ	*get_champ_by_id(t_list *champs, int id)
{
	t_champ		*champ;

	while (champs != NULL)
	{
		champ = champs->content;
		if (champ->id == id)
		{
			return (champ);
		}
		champs = champs->next;
	}
	return (NULL);
}

t_car	*create_car(int champ_id)
{
	t_car	*car;

	if ((car = ft_memalloc(sizeof(t_car))) == NULL)	// initialized with zeroes
	{
		perror("create_process");
		exit(-1);
	}
	car->regs[1] = -champ_id;	// TODO: ?
	return (car);
}

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

void	write_to_field(t_field *field, int place, char *exec_code, int size)
{
	int		k;

	field += place;
	k = 0;
	while (k < size)
	{
		field[k].square = exec_code[k];
		++k;
	}
}

void	load_champs(t_vm *vm)
{
	int const	step = MEM_SIZE / vm->champ_amount;
	int			id;
	t_champ		*champ;
	t_car		*car;

	ft_bzero(vm->arena, MEM_SIZE);
	vm->cars = NULL;
	id = 1;
	while (id <= vm->champ_amount)
	{
		champ = get_champ_by_id(vm->champs, id);
		write_to_field(vm->field, step * (id - 1), champ->exec_code, champ->size);
		car = create_car(k + 1);
		car->place = step * (id - 1);
		list_push(&(vm->cars), car);
		++id;
	}
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
	load_champs(vm);
	//
	dump_memory(vm->field);			// this is
	system("leaks -q corewar");		// here just
	exit(0);						// for testing
	//
	while (vm->cars != NULL /* ... */)
	{
		perform_round(vm);
	}
	// ...
}
