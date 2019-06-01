/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:57:24 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/01 16:57:22 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define INI		"Running in interactive mode...\n"
#define INI_COL	PF_CYAN INI PF_RESET

static void		show_init(t_vm *vm)
{
	ft_putstr(vm->color ? INI_COL : INI);
}

#define HNT1	"Enter \"dump[32|64]\" or a number of cycles to perform.\n"
#define HNT2	"Press Ctrl+D to quit.\n"
#define HNT		HNT1 HNT2
#define HNT_COL	PF_CYAN HNT PF_RESET

static void		show_hint(t_vm const *vm)
{
	ft_putstr(vm->color ? HNT_COL : HNT);
}

#define PRM		"(corewar) "
#define PRM_COL	PF_GREY PRM PF_RESET

static void		show_prompt(t_vm const *vm)
{
	ft_putstr(vm->color ? PRM_COL : PRM);
}

static int		get_number_or_dump(t_vm const *vm, char *line)
{
	int			number;

	number = 0;
	if (ft_strequ(line, "dump") || ft_strequ(line, "dump32"))
	{
		dump_memory(vm->field, 32);
	}
	else if (ft_strequ(line, "dump64"))
	{
		dump_memory(vm->field, 64);
	}
	else 
	{
		number = -1;
		if (is_only_digits(line))
		{
			number = ft_atoi(line);
		}
	}
	free(line);
	return (number);
}
/*
static void		loop_body(t_vm *vm, char *line)
{
	int const	number = get_number_or_dump(vm, line);

	if (number > 0)
	{
		vm->interactive_cycle += number;
		return ;
	}
	if (number != 0)
	{
		show_hint(vm);
	}
	show_prompt(vm);
}
*/
void			interactive_get(t_vm *vm)
{
	int			status;
	char		*line;
	int			number;

	if (vm->cycle == 0)
	{
		show_init(vm);
		show_hint(vm);
	}
	show_prompt(vm);
	while ((status = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		number = get_number_or_dump(vm, line);
		if (number > 0)
		{
			vm->interactive_cycle += number;
			return ;
		}
		if (number != 0)
		{
			show_hint(vm);
		}
		show_prompt(vm);
	}
	if (status == 0)
	{
		exit(0);	// ...
	}
	perror_exit("interactive_get");
}
