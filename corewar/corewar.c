/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/04/23 23:14:20 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int     main(int argc, char *argv[])
{
    if (argc == 1)
        e__args_amount();
    // if -dump set nbr_cycles to g_dump_mode
    system("leaks corewar");
    return (0);
}