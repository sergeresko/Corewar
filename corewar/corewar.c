/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/04/25 23:20:05 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int g_is_dump = FALSE;
int g_dump_cycles = -1;

void _test(t_player *players)
{
	ft_putendl("Test output!   < - - -\n");

	if (g_is_dump)
		ft_printf("Dump nbr_cycles: %d\n", g_dump_cycles);
	while (players)
	{
		ft_printf("Player's filename: %s\n", players->filename);
		ft_printf("Number: %d\n", players->number);
		players = players->next;
	}

	ft_putendl("\nEnd of test output!   < - - -\n");
}

int     main(int argc, char *argv[])
{
	t_player	*players;

    if (argc == 1)
        e__args_amount();
    players = check_arguments(argc, argv);

	_test(players);
	clean_players_list(&players);
    system("leaks corewar");
    return (0);
}

t_player	*check_arguments(int amount, char **args)
{
    int         i;
    int 		cur_number;
    t_player    *players;

    i = 1;

    players = NULL;
    while (i < amount)
    {
		cur_number = -1;
        if (ft_strequ(args[i], "-dump") && (i + 1) < amount)
        {
        	g_is_dump = TRUE;
			g_dump_cycles = ft_atoi(args[++i]);
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
			create_new_player(&players, args[i], cur_number);
        i++;
    }
    return (players);
}

void	create_new_player(t_player **players, const char *arg, int number)
{
	t_player	*new_player;

	if (!(new_player = ft_memalloc(sizeof(t_player))))
	{
		perror("Creating new player!");
		exit(-1);
	}
	new_player->filename = arg;
	new_player->number = check_player_number(players, number);
	if ((new_player->fd = open(new_player->filename, O_RDONLY)) == -1)
		e__open_file(new_player->filename);
	push_player_front(players, new_player);
}

void	push_player_front(t_player **players, t_player *player)
{
	if (!players)		// handle error
		ft_printf("Players list == NULL\n");
	if (players)
	{
		player->next = *players;
		*players = player;
	}
}

int		check_player_number(t_player **players, int number)
{
	t_player	*player;

	if (number != -1 && number < MAX_PLAYERS)
	{
		if (players && *players)
		{
			player = *players;
			while (player)
			{
				if (player->number == number)
					return (-1);
				player = player->next;
			}
			return (number);
		}
	}
	return (-1);
}

int		set_player_number(t_player **players, int number)
{
	return (1);
}

void	clean_players_list(t_player **players)
{
	if (players && *players)
	{
		if ((*players)->next)
			clean_players_list(&((*players)->next));
		ft_memdel((void **)players);
	}
}
