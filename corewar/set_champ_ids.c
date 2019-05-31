/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_champ_ids.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:28:48 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/31 12:37:51 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	TRUE or FALSE
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
**	return the smallest positive number that has not been used as id
*/

static int		choose_champ_id(t_list *champs)
{
	int			id;

	id = 1;
	while (already_used_id(champs, id))
	{
		++id;
	}
	return (id);
}

/*
**	assign id's to all champions who currently have a 0 in `id` field
*/

void			set_champ_ids(t_list *champs, int champ_amount)
{
	t_list		*item;
	t_champ		*champ;

	item = champs;
	while (item != NULL)
	{
		champ = item->content;
		if (champ->id == 0)
		{
			champ->id = choose_champ_id(champs);
		}
		else if (champ->id > champ_amount)
		{
			fatal_error("Champion id exceeds the total number of champions");
		}
		item = item->next;
	}
}
