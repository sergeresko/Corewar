/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_tricks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdmytro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/20 22:05:46 by mdmytro           #+#    #+#             */
/*   Updated: 2019/03/20 22:05:53 by mdmytro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			st_add_champion(t_champion **ch)
{
	t_chempion	*tmp;

	if (!(tmp = (t_champion *)malloc(sizeof(t_champion))))
		perror_exit("malloc was failed", 1);
	tmp->fd = -1;
	tmp->lives_num = 0;
	tmp->true_lives_num = 0;
	tmp->lust_live = 0;
	tmp->champs = 0;
	tmp->order = 0;
	tmp->op.magic = 0;
	tmp->op.prog_size = 0;
	ft_bzero(tmp->name_file, FILE_NAME_MAX + 1);
	ft_bzero(tmp->op.prog_name, PROG_NAME_LENGTH + 1);
	ft_bzero(tmp->op.comment, COMMENT_LENGTH + 1);
	ft_bzero(tmp->exec_code, CHAMP_MAX_SIZE);
	tmp->next = *ch;
	*ch = tmp;
}

void			st_reverse_champion(t_champion **ch)
{
	t_champion 	*a;
	t_champion 	*now;
	t_champion	*b;

	a = NULL;
	now = *ch;
	while (now)
	{
		b = now->next;
		now->next = a;
		a = now;
		now = b;
	}
	*ch = a;
}

void			st_free_champion(t_champion **ch)
{
	t_champion	*del;

	while (*ch)
	{
		del = *ch;
		*ch = (*ch)->next;
		free(del);
	}
}

int				st_reviwe_double_ch_num(t_champion *ch, int order)
{
	while (ch)
	{
		if (ch->order == order)
			return (1);
		ch = ch->next;
	}
	return (0);
}
