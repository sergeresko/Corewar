/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/14 22:53:25 by vlvereta         ###   ########.fr       */
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
    read_headers(players);

//	_test(players);
	clean_players_list(&players);
    system("leaks corewar");
    return (0);
}

t_player	*check_arguments(int amount, char **args)
{
    int         i;
    int 		cur_number;
    t_player    *players;
	static int	players_amount = 0;

	i = 1;

    players = NULL;
	cur_number = -1;
    while (i < amount)
    {
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
        {
			create_new_player(&players, args[i], &cur_number);
			if (++players_amount > MAX_PLAYERS)
			{
				ft_putendl("Max players number exceeded!");
				exit(-1);
			}
		}
        i++;
    }
	set_players_numbers(players, players_amount);
    return (players);
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
	int 		numbers[amount];
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
		ft_memdel((void **)players);
	}
}

/*
 * Helpers
 */
char	*clean_from_whitespaces(char *str)
{
	int		i;
	int		len;
	char	*result;
	char	*temporary;

	i = 0;
	result = NULL;
	len = ft_strlen(str);
	if (!(temporary = ft_strnew(sizeof(char) * len)))
	{
		perror("clean_from_whitespaces");
		exit(-1);
	}
	while (*str)
	{
		if (*str != ' ' && *str != '\n')
			temporary[i++] = *str;
		str++;
	}
	if (!(result = ft_strsub(temporary, 0, ft_strlen(temporary))))
	{
		perror("clean_from_whitespaces");
		exit(-1);
	}
	ft_strdel(&temporary);
	return (result);
}

/*
 * Read and validation part
 */
void	read_headers(t_player *players)
{
	char	*header;
	char	*clean_header;

	if (!(header = ft_strnew(sizeof(char) * CHAR_HEADER)))
	{
		perror("read_headers");
		exit(-1);
	}
	while (players)
	{
		ft_bzero(header, CHAR_HEADER);
		if (read(players->fd, header, CHAR_HEADER) != -1
			&& (clean_header = clean_from_whitespaces(header)))
		{
			ft_printf("%s\n", clean_header);
			check_magic(clean_header);

			ft_strdel(&clean_header);
		}
		else
		{
			ft_printf("Player %s header isn't in order!\n", players->filename);
			exit(-1);
		}
		players = players->next;
	}
	ft_strdel(&header);
}

void	check_magic(char *header)
{
	char	*magic;

	if (!(magic = ft_strsub(header, 0, BYTE)))
	{
		perror("check_magic");
		exit(-1);
	}
	ft_printf("%s === %s\n", magic, convert_int_to_hex(COREWAR_EXEC_MAGIC));
}
