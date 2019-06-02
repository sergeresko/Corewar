/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:13:00 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/02 17:13:22 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char			**get_opt_bonus(t_vm *vm, char **av)
{
	char		*arg;

	while ((arg = *(++av)) != NULL)
	{
		if (ft_strequ(arg, "-h") || ft_strequ(arg, "-help"))
			vm->opt.help = TRUE;
		else if (ft_strequ(arg, "-v") || ft_strequ(arg, "-verbose"))
			vm->opt.verbose = TRUE;
		else if (ft_strequ(arg, "-s") || ft_strequ(arg, "-silent"))
			vm->opt.silent = TRUE;
		else if (ft_strequ(arg, "-C") || ft_strequ(arg, "-canonic"))
			vm->opt.canonic = TRUE;
		else if (ft_strequ(arg, "-c") || ft_strequ(arg, "-color"))
			vm->opt.color = TRUE;
		else if (ft_strequ(arg, "-l") || ft_strequ(arg, "-leaks"))
			vm->opt.leaks = TRUE;
		else if (ft_strequ(arg, "-i") || ft_strequ(arg, "-interactive"))
			vm->interactive_cycle = 0;
		else
			break ;
	}
	return (av - 1);
}
