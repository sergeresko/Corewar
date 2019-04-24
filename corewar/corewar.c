/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/04/24 23:27:22 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	_test()
{
	if (g_is_dump)
		ft_printf("Dump nbr_cycles: %d\n", g_dump_cycles);
}

int     main(int argc, char *argv[])
{
    if (argc == 1)
        e__args_amount();
    check_arguments(argc, argv);
    _test();
    system("leaks corewar");
    return (0);
}

void    check_arguments(int amount, char **args)
{
    int         i;
    int 		current_n;
//    t_player    *players;

    i = 1;
    current_n = -1;
//    players = NULL;
    while (i < amount)
    {
        if (ft_strequ(args[i], "-dump") && (i + 1) < amount)
        {
        	g_is_dump = TRUE;
			g_dump_cycles = ft_atoi(args[++i]);
		}
        else if (ft_strequ(args[i], "-n") && (i + 1) < amount)
			current_n = ft_atoi(args[++i]);
        else
            ft_printf("Player name: %s\n", args[i]);
        i++;
    }
}
