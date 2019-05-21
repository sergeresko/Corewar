/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disassembler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 17:57:43 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/21 18:12:12 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_filename(const char *filename)
{
	int		i;
	char	**splitname;

	if (!(splitname = ft_strsplit(filename, '.')))
	{
		perror("check_filename");
		exit(-1);
	}
	i = 0;
	while (splitname[i])
	{
		if (!splitname[i + 1] && !ft_strequ(splitname[i], "cor"))
		{
			ft_printf("\"%s\" is NOT a correct filename!\n", filename);
			exit(-1);
		}
		i++;
	}
	i = 0;
	while (splitname[i])
		ft_strdel(&(splitname[i++]));
}

void	disassemble_processing(int fd, const char *filename)
{
	ft_printf("Disassemble processing!\n");
	check_filename(filename);
}
