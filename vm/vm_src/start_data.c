/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 21:07:49 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/21 19:04:46 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void	data_with_color(t_cw *cw)
{
	t_champ	champ;
	int		k;

	k = 0;
	ft_printf("\033[90mIntroducing contestants...\n\033[0m");
	while (k < cw->champs_amount)
	{
		champ = cw->champ[k];
		if (champ.id == 1)
			ft_printf("%s", PURPLE);
		else if (champ.id == 2)
			ft_printf("%s", BLUE);
		else if (champ.id == 3)
			ft_printf("%s", YELLOW);
		else if (champ.id == 4)
			ft_printf("%s", RED);
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
		champ.num, champ.exec_amount, champ.name, champ.comment);
		ft_printf("%s", DEF);
		k += 1;
	}
}

void		start_data(t_cw *cw)
{
	t_champ	champ;
	int		k;

	k = 0;
	if (cw->ind->c)
		data_with_color(cw);
	else
	{
		ft_printf("Introducing contestants...\n");
		while (k < cw->champs_amount)
		{
			champ = cw->champ[k];
			ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
			champ.num, champ.exec_amount, champ.name, champ.comment);
			k += 1;
		}
	}
}
