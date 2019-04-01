/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ozalisky <ozalisky@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/02/10 15:14:19 by ozalisky         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdio.h>

# include "op.h"
# include "../libft/includes/libft.h"

# define MAX_COUNTER 4294967295

# define BYTE 8
# define HEX_HEADER 4384
# define HEX_NAME_LENGTH 256
# define HEX_DESCRIPTION_LENGTH 4096

# define STDOUT "Process has to be printed to STDOUT but this functional doesn't ready yet :("
# define NO_ARGS_ERROR "Usage: ./asm [-a] <sourcefile.s>\n    -a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output"
# define READ_FILE_ERROR "Cannot read file"
# define ALLOCATION_ERROR "Cannot allocate memory"

// keep champ's header
typedef struct		s_champ_header
{
	unsigned int	size;
	char			name[HEX_NAME_LENGTH + 1];
	char			description[HEX_DESCRIPTION_LENGTH + 1];
}					t_champ_header;

// keep pointers to champ's location where we should paste value
typedef struct		s_addr
{
	char			*addr;
	struct s_addr	*next;
}					t_addr;

// keep list of labels
typedef struct		s_label
{
	int 			index;
	char 			*name;
	t_addr			*addr;
	struct s_label	*next;
}					t_label;

// keep list of data for error management
typedef struct		s_data
{
	int				line;
	int				row;
	int				command_counter;
	int				errorCase;
	int				skippedLine;
}					t_data;

// main structure with all valuable content
typedef struct		s_asm
{
	t_champ_header	header;
	t_label			*labels;
	t_data			data;
	char 			*filename;
	unsigned int	counter;

}					t_asm;

int		asm_init(t_asm **asm_struct, const char *argv);
char	*get_filename(const char *argv);
void	file_processing(int fd, const char *argv);
int		check_line(char **line, t_asm *asm_struct);

int		get_substr_index(const char *big, const char *little);
int		is_skipable(char **line, t_asm *asm_struct);
void	clean_asm_struct(t_asm **asm_struct);

/*
 * Errors functions
 */
void	e__no_args(void);
void	e__open_file(const char *name);
void	e__read_file(t_asm *asm_struct, int errorCase);

void	output_to_file(t_asm *champ);
void	format_file_output(int fd, char *champ);
char	*convert_int_to_hex(int num);


char	*make_header_string(t_champ_header *header);

int 	check_for_command(char **line, t_asm *asm_struct, int start);

void	clean_labels_list(t_label **labels);
int		new_label(t_label **labels, char *name, int index);

int 	read_file(int fd, t_asm *asm_struct);
char	*get_trimmed_line(char **line,t_asm *asm_struct);


/*
 * Set champ's name and description
 */
void	get_champs_name(char *line, t_asm *asm_struct);
void	make_hex_name(char *hex_name, char *name);
void	get_champs_description(char *line, t_asm *asm_struct);
void	make_hex_description(char *hex_description, char *description);

/*
 * Functions
 */
char	*get_label_name(char **tline);
char	*cut_some_piece(char *line, unsigned int start);
t_label	*new_label_node(char *label_name);
void	push_label_front(t_label **labels, t_label *label);

#endif
