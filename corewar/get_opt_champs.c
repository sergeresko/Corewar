/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opt_champs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:28:48 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/28 16:20:23 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	returns TRUE or FALSE
*/

static int		already_used_id(t_list *champs, int id)
{
	t_champ		*champ;

	while (champs != NULL)
	{
		champ = champs->content;
		if (champ->id == id)
			return (TRUE);
		champs = champs->next;
	}
	return (FALSE);
}

/*
**	make sure that the filename ends in ".cor";
**	append a new champion to `vm->champs`
**	with initialized `id` and `filename` fields
*/

static void		add_champ(t_vm *vm, int id, char const *filename)
{
	char *const	extension = ft_strrchr(filename, '.');
	t_champ		*champ;
   
	if (extension == NULL || !ft_strequ(extension, ".cor"))
	{
		throw_error("Champion file must have .cor extention");
	}
	if ((champ = malloc(sizeof(t_champ))) == NULL)
	{
		perror("add_champion");
		exit(-1);
	}
	champ->id = id;
	if ((champ->filename = ft_strdup(filename)) == NULL)
	{
		perror("add_champion");
		exit(-1);
	}
	list_push_back(&(vm->champs), champ);
}

/*
**	create a list of champions in `vm->champs`,
**	setting their `id` to a number specified with "-n" option
**	or to 0 if there is no option
*/

void			get_opt_champs(t_vm *vm, char const **av)
{
	char		*arg;
	int			id;

	while ((arg = *(++av)) != NULL)
	{
		id = 0;
		if (ft_strequ(arg, "-n"))
		{
			if ((arg = *(++av)) == NULL
					|| (id = ft_atoi(arg)) < 0 || id > MAX_PLAYERS
					|| already_used_id(vm->champs, id))
			{
				throw_error("Invalid value for option -n");
			}
			if ((arg = *(++av)) == NULL)
			{
				throw_error("No champion after setting number with -n");
			}
		}
		if (++(vm->champ_amount) > MAX_PLAYERS)
		{
			throw_error("Too many players");
		}
		add_champ(vm, id, arg);
	}
}
