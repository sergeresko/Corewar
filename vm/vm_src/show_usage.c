/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_usage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:20:33 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/20 18:20:34 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	show_usage(t_cw *data)
{
	char	*row;
	int		fd;

	data->ind->u = 1;
	if (data->fail_sense)
		fail(data);
	if (data->ind->c)
		ft_printf("%s", AQUAMARINE);
	row = NULL;
	fd = open("usage_cw", O_RDONLY);
	while (get_next_line(fd, &row) == 1)
	{
		ft_putendl(row);
		ft_strdel(&row);
	}
	if (data->ind->c)
		ft_printf("%s", DEF);
	if (data->ind->l)
		system("leaks corewar");
	exit(0);
}
