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

# define MAX_COUNTER 4294967295

# define STDOUT "Process has to be printed to STDOUT but this functional doesn't ready yet :("
# define NO_ARGS_ERROR "Usage: ./asm [-a] <sourcefile.s>\n    -a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output"
# define READ_FILE_ERROR "Cannot read file"
# define ALLOCATION_ERROR "Cannot allocate memory"

typedef struct      s_addr //структура для хранения адресов мест положения лейблов в чемпионе
{
    char            *addr;
    struct s_addr   *next;
}                   t_addr;

typedef struct		s_label
{
	int 			index;
	char 			*name;
	t_addr          *addr;
	struct s_label	*next;
}					t_label;

typedef struct      s_asm
{
	t_header        *header;
	t_label         *labels;
	char 			*filename;
    unsigned int    counter;

}                   t_asm;

int		asm_init(t_asm **asm_struct, const char *argv);
char	*get_filename(const char *argv);
void	file_processing(int fd, const char *argv);
int		get_labels(int fd, t_asm *asm_struct);
int		check_line(char *tline, t_asm *asm_struct);

char	*check_comment(char **line);
void	clean_asm_struct(t_asm **asm_struct);

/*
 * Errors functions
 */
void	e__no_args(void);
void	e__open_file(const char *name);

#endif
