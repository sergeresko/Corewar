/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fail.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:21:12 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/20 18:21:14 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	fail_sense(t_cw *data, char *sense)
{
	data->fail_sense = sense;
	fail(data);
}

void	fail(t_cw *data)
{
	if (data->ind->t)
		system("afplay music/"%FAIL_MUSIC%".mp3&");
	if (data->ind->c)
		ft_printf("%s", RED);
	ft_printf("FAIL: %s.\n", data->fail_sense);
	if (data->ind->c)
		ft_printf("%s", DEF);
	if (!data->ind->u)
	{
		if (data->ind->l)
			system("leaks corewar");
		exit(1);
	}
}
