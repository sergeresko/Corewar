/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 18:13:00 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/29 18:25:01 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char	**get_opt_bonus(t_vm *vm, char **av)
{
	char	*arg;

	while ((arg = *(++av)) != NULL)
	{
		if (ft_strequ(arg, "-h") || ft_strequ(arg, "-help"))
		{
			vm->help = TRUE;
		}
		else if (ft_strequ(arg, "-v") || ft_strequ(arg, "-verbose"))
		{
			vm->verbose = TRUE;
		}
		else if (ft_strequ(arg, "-c") || ft_strequ(arg, "-color"))
		{
			vm->color = TRUE;
		}
		else
		{
			break ;
		}
	}
	return (av - 1);
}
