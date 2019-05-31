/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 16:28:02 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 12:38:39 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			perror_exit(char const *prefix)
{
	perror(prefix);
	exit(-1);
}

void			fatal_error(char const *message)
{
	ft_printf("ERROR: %s.\n", message);
	exit(-1);
}
