/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdmytro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 15:48:35 by mdmytro           #+#    #+#             */
/*   Updated: 2019/02/25 15:48:38 by mdmytro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			check_magic(t_chempion *ch)
{
	uint8_t			buf[REG_SIZE];

	ft_bzero(buf, REG_SIZE);
	if ((read(ch->fd, buf, REG_SIZE)) < 0)
		exit_perror(ch->name_file, 4);
	ch->op.magic = hex_to_dec(buf, 4);
	if (ch->op.magic != COREWAR_EXEC_MAGIC)
		exit(ch->name_file, 9);
}

static void			separator_skip(char *name_f, int fd, const long size)
{
	uint32_t		i;
	uint8_t			buf[size];

	if ((read(fd, buf, size)) < 0)
		exit_perror(name_f, 4);
	i = -1;
	while (++i < size)
		if (buf[i] != 0)
			exit(name_f, 10);
}

static void			champ_name_and_code(t_chempion *ch)
{
	uint8_t			buf[REG_SIZE];
	int8_t			tmp[PROG_NAME_LENGTH + 1];

	ft_bzero(buf, REG_SIZE);
	ft_bzero(tmp, PROG_NAME_LENGTH + 1);
	if ((g_core.pd.reserve = read(ch->fd, tmp, PROG_NAME_LENGTH)) < 0)
		exit_perror(ch->name_file, 4);
	else if (g_core.pd.reserve < PROG_NAME_LENGTH)
		exit(ch->name_file, 9);
	ft_strcpy(ch->op.prog_name, tmp);
	separator_skip(ch->name_file, ch->fd, REG_SIZE);
	if ((read(ch->fd, buf, REG_SIZE)) < 0)
		exit_perror(ch->name_file, 4);
	ch->op.prog_size = hex_to_dec(buf, 4);
	if (ch->op.prog_size > CHAMP_MAX_SIZE)
	{
		g_core.pd.reserve = ch->op.prog_size;
		exit(ch->name_file, 9);
	}
}

static void			comment_and_exec(t_chempion * ch)
{
	uint8_t		buf[ch->op.prog_size + 2];
	int8_t		tmp[COMMENT_LENGTH + 1];

	ft_bzero(tmp, COMMENT_LENGTH + 1);
	ft_bzero(buf, ch->op.prog_size + 2);
	if ((g_core.pd.reserve = read(ch->fd, tmp, COMMENT_LENGTH)) < 0)
		exit_perror(ch->name_file, 4);
	else if (g_core.pd.reserve < COMMENT_LENGTH)
		exit(ch->name_file, 9);
	ft_strcpy(ch->op.comment, tmp);
	separator_skip(ch->name_file, ch->fd, REG_SIZE);
	if ((g_core.pd.reserve = read(ch->fd, buf, ch->op.prog_size + 1)) < 0)
		exit_perror(ch->name_file, 4);
	if ((uint32_t)g_core.pd.reserve != ch->op.prog_size)
		exit(ch->name_file, 11);
	ft_memcpy(ch->exec_code, buf, ch->op.prog_size);
}

void				parser(void)
{
	t_chempion	*ch;

	ch = g_core.pd.champs;
	while (ch)
	{
		check_magic(ch);
		champ_name_and_code(ch);
		comment_and_exec(ch);
		close(ch->fd);
		ch = ch->next;
	}
}