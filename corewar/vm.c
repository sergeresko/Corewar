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

// -------------

void		list_push(t_list **head, void *content)
{
	t_list	*item;

	item = malloc(sizeof(t_list));		// TODO: check if not NULL
	item->content = content;
	item->next = *head;
	*head = item;
}

void		list_pop(t_list **head)
{
	t_list	*item;

	item = *head;
	*head = item->next;
	free(item);
}

// -------------

/*
**	returns TRUE or FALSE
*/

int		is_valid_opcode(char c)		// t_bool
{
	return (1 <= c && c <= 16);
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

static t_player	*get_player_by_number(t_vm *vm, int n)
{
	t_player	*player;

	player = vm->players;
	while (player)
	{
		if (player->number == n)
		{
			return (player);
		}
		player = player->next;
	}
	return (NULL);
}

t_car	*create_car(int player_number)
{
	t_car	*car;

	if ((car = ft_memalloc(sizeof(t_car))) == NULL)	// initialized with zeroes
	{
		perror("create_process");
		exit(-1);
	}
	car->regs[0] = -player_number;	// TODO: ?
	return (car);
}

void	load_players(t_vm *vm)
{
	int const	step = MEM_SIZE / vm->nbr_players;
	int			k;
	t_player	*player;
	t_car		*car;

	ft_bzero(vm->arena, MEM_SIZE);
	vm->cars = NULL;
	k = 0;
	while (k < vm->nbr_players)
	{
		player = get_player_by_number(vm, k + 1);
		ft_memcpy(vm->arena + step * k, player->exec_code, player->size); // TODO:
		car = create_car(k + 1);
		car->place = step * k;
		list_push(&(vm->cars), car);
		++k;
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
	load_players(vm);
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
