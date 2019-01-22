/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/11/08 20:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		asm_init(t_asm **asm_struct, const char *argv)
{
	if (!(*asm_struct = ft_memalloc(sizeof(t_asm))))
	{
		perror(ALLOCATION_ERROR);
		return (0);
	}
	if (!((*asm_struct)->filename = get_filename(argv)))
	{
		clean_asm_struct(asm_struct);
		return (0);
	}
	(*asm_struct)->counter = MAX_COUNTER;
	return (1);
}

char	*get_filename(const char *argv)
{
	int	start;
	int	len;

	len = ft_strlen(argv);
	if (len <= 2 || argv[len - 1] != 's' || argv[len - 2] != '.')
		return (NULL);
	start = len - 1;
	while (start >= 0 && argv[start] != ' ' && argv[start] != '/')
		start--;
	start++;
	return (ft_strsub(argv, start, len - start - 2));
}

void	clean_asm_struct(t_asm **asm_struct)
{
	if ((*asm_struct)->filename)
		ft_memdel((void **)&((*asm_struct)->filename));
	if ((*asm_struct)->labels)
		clean_labels_list(&((*asm_struct)->labels));
	ft_memdel((void **)asm_struct);
}

void	clean_labels_list(t_label **labels)
{
	if (labels && *labels)
	{
		ft_strdel(&((*labels)->name));
		if ((*labels)->next)
			clean_labels_list(&((*labels)->next));
		ft_memdel((void **)labels);
	}
}