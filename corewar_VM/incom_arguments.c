/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   incom_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdmytro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 17:58:06 by mdmytro           #+#    #+#             */
/*   Updated: 2019/03/04 17:58:07 by mdmytro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void truth_champ(char *name_file)
{
	int32_t	i;

	if (g_core.pd.count_ch == MAX_PLAYERS)
		exit("Error: Champs overflow", 13);
	if (g_core.pd.reserve != 0 && st_reviwe_double_ch_num(g_core.pd.ch,\
		(int)g_core.pd.reserve))
		exit("Error: More than need champs number", 12);
	if ((i = open(name_file, O_RDONLY)) == -1 || read(i, NULL, 0) == -1)
		perror_exit(name_file, 14);
	st_add_champion(&g_core.pd.ch);
	g_core.pd.ch->fd = i;
	ft_strcpy(g_core.pd.ch->name_file, name_file);
	if (g_core.pd.reserve != 0)
		g_core.pd.flag_quant_ch[g_core.pd.count_ch] = '1';
	++g_core.pd.count_ch;
	g_core.pd.ch->order = (int)g_core.pd.reserve;
	g_core.pd.reserve = 0;
}

static void	number_of_champion(char **argv, int *i)
{
	*i++;
	if (!argv[*i] || ft_str_is_digit(argv[*i]))
		exit("Error: Argument is not number after -n", 12);
	g_core.pd.reserve = ft_atoi_max(argv[*i]);
	if (g_core.pd.reserve < 1 || g_core.pd.reserve > MAX_PLAYERS)
		exit("Error: Argument is not valid after -n", 12);
	*i++;
	if (!argv[*i])
		exit("Error: No champion after -n", 12);
	truth_champ(argv[*i]);
}

static void		set_count_ch(t_champion **ch)
{
	t_champion	*head;
	int32_t		count;
	int32_t		order;
	int32_t		i;

	i = -1;
	count = -1;
	order = g_core.pd.count_ch;
	head = ch;
	while (ch)
	{
		ch->champs = count--;
		if (!g_core.pd.flag_quant_ch[++i])
		{
			while (st_reviwe_double_ch_num(head, order))
				order--;
			ch->order = order;
		}
		ch = ch->next;
	}
}

void		incom_arguments(int argc, char **argv)
{
	int32_t	i;

	if (argc < 2)
		exit("", 1);
	i = parse_flag(argv);
	while (argv[i])
	{
		if (!ft_strcmp(argv[i], "-n"))
			number_of_champion(argv, &i);
		else
			truth_champ(argv[i]);
		i++;
	}
	if (!g_core.pd.ch)
		exit("Error: No champs", 2);
	
}
