/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_get.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 12:57:24 by syeresko          #+#    #+#             */
/*   Updated: 2019/06/04 16:01:04 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

#define INIT		"Running in interactive mode...\n"

#define HINT_1		"Enter a number of cycles to perform "
#define HINT_2		"or type \"dump[32|64]\" (shortcuts: \"d | dd\").\n"
#define HINT_3		"Press Ctrl-D to quit.\n"
#define HINT		HINT_1 HINT_2 HINT_3

#define PROMPT		"(corewar) "
#define PROMPT_COL	PF_GREY PROMPT PF_RESET

/*
**	parse and free the line;
**	if the line tells to make a dump, make it and return 0;
**	if the line specifies a positive integer, increase `vm->interactive_cycle`
**	by this number and return the number;
**	otherwise return -1
*/

static int		set_interactive_cycle_or_make_dump(t_vm *vm, char *line)
{
	int			number;

	number = 0;
	if (ft_strequ(line, "d")
			|| ft_strequ(line, "dump") || ft_strequ(line, "dump32"))
	{
		dump_memory(vm, 32);
	}
	else if (ft_strequ(line, "dd") || ft_strequ(line, "dump64"))
	{
		dump_memory(vm, 64);
	}
	else
	{
		number = -1;
		if (is_only_digits(line))
		{
			number = ft_atoi(line);
			vm->interactive_cycle += number;
		}
	}
	free(line);
	return (number);
}

/*
**	TRUE or FALSE
*/

static int		process_line(t_vm *vm, char *line)
{
	int const	number = set_interactive_cycle_or_make_dump(vm, line);

	if (number > 0)
	{
		return (TRUE);
	}
	if (number != 0)
	{
		ft_putstr(HINT);
	}
	ft_putstr(vm->opt.color ? PROMPT_COL : PROMPT);
	return (FALSE);
}

/*
**	NOTE: This function terminates the program.
*/

static void		finalize(t_vm const *vm, int status)
{
	ft_putchar('\n');
	if (status != 0)
	{
		perror_exit("interactive_get");
	}
	if (vm->opt.leaks)
	{
		system(LEAKS_COMMAND);
	}
	exit(0);
}

/*
**	read commands from the user until he enters a valid number of cycles
**	to perform or terminates the program (if he asks for a dump, the dump
**	is printed but he's still prompted to enter the next command)
*/

void			interactive_get(t_vm *vm)
{
	int			status;
	char		*line;

	if (vm->cycle == 0)
	{
		ft_putstr(INIT);
		ft_putstr(HINT);
	}
	ft_putstr(vm->opt.color ? PROMPT_COL : PROMPT);
	while ((status = get_next_line(STDIN_FILENO, &line)) > 0)
	{
		if (process_line(vm, line))
		{
			return ;
		}
	}
	finalize(vm, status);
}
