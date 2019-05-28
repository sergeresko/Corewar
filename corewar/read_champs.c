/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_champs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:42:14 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/28 16:32:15 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	read executable code and validate its size;
**	store it in `exec_code` field of `champ`
*/

static void		read_champion_exec_code(int fd, t_champ *champ)
{
	int			size;
	char		c;

	if ((champ->exec_code = malloc(champ->size)) == NULL)
	{
		perror("read_champ_exec_code");
		exit(-1);
	}
	if ((size = read(fd, champ->exec_code, champ->size)) == -1)
	{
		perror("read_champ_exec_code");
		exit(-1);
	}
	if (size != champ->size || read(fd, &c, 1) != 0)
	{
		ft_printf("ERROR: Size mismatch in \"%s\".\n", champ->filename);
		exit(-1);
	}
}

/*
**	read the contents of `champ->filename` and parse it into respective
**	fields of `champ`
*/

static void		read_champion(t_champ *champ)
{
	int			fd;

	if ((fd = open(champ->filename)) < 0)
	{
		perror("read_champion");
		exit(-1);
	}
	read_champ_header(fd, champ);
	raed_champ_exec_code(fd, champ);
	close(fd);
}

void			read_champs(t_list *champs)
{
	while (champs != NULL)
	{
		read_champion(champs->content);
		champs = champs->next;
	}
}
