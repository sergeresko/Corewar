/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/09/30 20:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdio.h>

# include "op.h"
# include "../../libft/includes/libft.h"

# define STDOUT "Process has to be printed to STDOUT but this functional doesn't ready yet :("
# define NO_ARGS_ERROR "Usage: ./asm [-a] <sourcefile.s>\n    -a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output"
# define READ_FILE_ERROR "Cannot read file"
# define ALLOCATION_ERROR "Cannot allocate memory"

typedef struct		s_label
{
	int 			l_ind;
	char 			*name;
	struct s_label	*next;
}					t_label;

void	file_processing(int fd, const char *name);
int		head_init(t_header **header, t_label **labels);

char	*check_comment(char **line);
void	clean_and_exit(void **ptr);

/*
 * Errors functions
 */
void	e__no_args(void);
void	e__read_file(int fd);
void	e__open_file(const char *name);

#endif
