/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <syeresko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/23 15:59:46 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	read_exec_code(t_player *players)
{
	char	c;

	while (players)
	{
		if ((players->exec_code = malloc(players->size)) == NULL
				|| read(players->fd, players->exec_code, players->size) != players->size)
		{
			perror("read_exec_code");
			exit (-1);
		}
		if (read(players->fd, &c, 1) != 0)
		{
			ft_printf("Size mismatch for player \"%s\"\n", players->name);
			exit(-1);
		}
		players = players->next;
	}
}

void _test(t_vm const *vm)
{
	t_player	*player;

	player = vm->players;
	ft_putendl("Test output!   < - - -\n");
	if (vm->is_dump)
		ft_printf("Dump nbr_cycles: %d\n", vm->dump_cycles);
	while (player)
	{
        ft_printf("Name: \"%s\"\n", player->name);
		ft_printf("Number: %d\n", player->number);
		ft_printf("Size: %d\n", player->size);
        ft_printf("Comment: \"%s\"\n", player->comment);
        ft_printf("Player's filename: \"%s\"\n", player->filename);
		player = player->next;
	}
	ft_putendl("\nEnd of test output!   - - - >\n");
}

int     main(int argc, char *argv[])
{
	t_vm	vm;

    if (argc == 1)
        e__args_amount();
    check_arguments(&vm, argc, argv);
    read_headers(vm.players);
	read_exec_code(vm.players);

	_test(&vm);

	perform_battle(&vm);

	clean_players_list(&(vm.players));		// not needed
    system("leaks -q corewar");
    return (0);
}

void	check_arguments(t_vm *vm, int amount, char **args)
{
    int         i;
    int 		cur_number;

	vm->is_dump = FALSE;
	vm->dump_cycles = -1;
    vm->players = NULL;
	vm->nbr_players = 0;
	i = 1;
	cur_number = -1;
    while (i < amount)
    {
        if (ft_strequ(args[i], "-dump") && (i + 1) < amount)
        {
        	vm->is_dump = TRUE;
			vm->dump_cycles = ft_atoi(args[++i]);
			if (amount == i + 1)
				exit_with_usage();
		}
        else if (ft_strequ(args[i], "-n") && (i + 1) < amount)
        {
			cur_number = ft_atoi(args[++i]);
			if (amount == i + 1)
				exit_with_usage();
		}
        else
        {
			create_new_player(&(vm->players), args[i], &cur_number);
			if (++(vm->nbr_players) > MAX_PLAYERS)
			{
				ft_putendl("Max players number exceeded!");
				exit(-1);
			}
		}
        i++;
    }
	set_players_numbers(vm->players, vm->nbr_players);
}

void	create_new_player(t_player **players, const char *arg, int *n)
{
	int 		number;
	t_player	*new_player;

	number = *n;
	if (!(new_player = ft_memalloc(sizeof(t_player))))
	{
		perror("Create new player");
		exit(-1);
	}
	new_player->self = FALSE;
	new_player->filename = arg;
	new_player->number = check_player_number(players, arg, MAX_PLAYERS, number);
	if ((new_player->fd = open(new_player->filename, O_RDONLY)) == -1)
		e__open_file(new_player->filename);
	push_player_back(players, new_player);
	*n = -1;
}

void	push_player_back(t_player **players, t_player *player)
{
	t_player	*temp;

	if (!players)		// handle error
		ft_printf("Players list == NULL\n");
	if (players && *players)
	{
		temp = *players;
		while (temp->next)
			temp = temp->next;
		temp->next = player;
	}
	else
		*players = player;
}

int		check_player_number(t_player **players, const char *self_name, int max, int number) {
	t_player *player;

	if (number > max)
	{
		ft_printf("Player '%s' specifies number (%d) higher than players amount\n", self_name, number);
		exit(-1);
	}
	if (number != -1 && number <= max)
	{
		if (players && *players)
		{
			player = *players;
			while (player)
			{
				if (!player->self && player->number == number)
				{
					ft_printf("Player '%s' specifies number (%d) which another player has already set\n", self_name, number);
					exit(-1);
				}
				player->self = FALSE;
				player = player->next;
			}
		}
		return (number);
	}
	return (-1);
}

void	set_players_numbers(t_player *players, int amount)
{
	int 		n;
	int 		numbers[amount];	// can't do this thing according to the Norm
	t_player	*temp;

	ft_bzero(numbers, sizeof(int) * amount);
	temp = players;
	while (temp)
	{
		temp->self = TRUE;
		if ((n = check_player_number(&players, temp->filename, amount, temp->number)) != -1)
			numbers[n - 1] = 1;
		temp = temp->next;
	}
	n = -1;
	while (players)
	{
		if (players->number == -1)
		{
			while (numbers[++n])
				;
			players->number = n + 1;
		}
		players = players->next;
	}
}

void	clean_players_list(t_player **players)
{
	if (players && *players)
	{
		if ((*players)->next)
			clean_players_list(&((*players)->next));
		ft_strdel(&((*players)->name));
        ft_strdel(&((*players)->comment));
		free((*players)->exec_code);
		ft_memdel((void **)players);
	}
}
