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

void	list_push(t_list **head, void *content)
{
	t_list	*item;

	item = malloc(sizeof(t_list));
	item->content = content;
	item->next = *head;
	*head = item;
}

void	list_pop(t_list **head)
{
	t_list	*item;

	item = *head;
	*head = item->next;
	free(item);
}

// -------------

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
//		p->delay = vm->op[p->op_code].delay;	// TODO:
	}
	--(p->delay);
	if (p->delay == 0)
	{
//		execute_operation(vm, p);		// <---------- TODO:
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
		perform_process(vm, item->content);
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
	addr = &(vm->processes);
	while (*addr != NULL)
	{
		p = (*addr)->content;
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

static void	print_hex(unsigned char b)
{
	char	s[2];

	s[0] = (char)(b / 16);
	s[0] += (s[0] < 10) ? '0' : ('a' - 10);
	s[1] = (char)(b % 16);
	s[1] += (s[1] < 10) ? '0' : ('a' - 10);
	write(1, s, 2);
}

void	dump_memory(void const *arena)
{
	char const	*s;
	int			i;

	s = arena;
	i = 0;
	while (i < MEM_SIZE)
	{
		print_hex(s[i]);
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

t_process	*create_process(int player_number)
{
	t_process	*p;

	if ((p = ft_memalloc(sizeof(t_process))) == NULL)	// initialized with zeroes
	{
		perror("create_process");
		exit(-1);
	}
	p->registers[0] = -player_number;	// TODO: ?
	return (p);
}

void	load_players(t_vm *vm)
{
	int const	step = MEM_SIZE / vm->nbr_players;
	int			i;
	t_player	*player;
	t_process	*process;

	ft_bzero(vm->arena, MEM_SIZE);
	vm->processes = NULL;
	i = 0;
	while (i < vm->nbr_players)
	{
		player = get_player_by_number(vm, i + 1);
		ft_memcpy(vm->arena + step * i, player->exec_code, player->size);
		process = create_process(i + 1);
		process->pc = step * i;
		list_push(&(vm->processes), process);
		++i;
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
	dump_memory(vm->arena);			// this is
	system("leaks -q corewar");		// here just
	exit(0);						// for testing
	//
	while (vm->processes != NULL /* ... */)
	{
		perform_round(vm);
	}
	// ...
}
