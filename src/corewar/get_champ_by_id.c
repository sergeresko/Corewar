/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_champ_by_id.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 20:47:12 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/29 20:48:13 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_champ			*get_champ_by_id(t_list *champs, int champ_id)
{
	t_champ		*champ;

	while (champs != NULL)
	{
		champ = champs->content;
		if (champ->id == champ_id)
		{
			return (champ);
		}
		champs = champs->next;
	}
	return (NULL);
}
