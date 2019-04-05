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
# include "errors.h"
# include "../libft/includes/libft.h"

# define MAX_COUNTER 4294967295

#define TRUE 1
#define FALSE 0
# define BYTE 8
# define HEX_HEADER 4384


typedef struct		s_header
{
	unsigned int	size;
	char			name[HEX_NAME_LENGTH + 1];
	char			description[HEX_DESC_LENGTH + 1];
}					t_header;

typedef struct		s_label
{
	int 			index;
	char 			*name;
	struct s_label	*next;
}					t_label;

typedef struct		s_data
{
	int				line;
	int				row;
	int				command_counter;
	int				errorCase;
	int				skippedLine;
}					t_data;

typedef struct		s_com
{
	char			code;
	char			codage;
	int				label_size;
	struct s_com	*next;
}					t_com;

typedef struct		s_asm
{
	t_header		header;
	t_label			*labels;
	t_com			*command;
	t_com			*commands;
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
void	clean_commands_list(t_com **commands);

/*
 * Errors functions
 */
void	e__no_args(void);
void	e__open_file(const char *name);
void	e__read_file(t_asm *asm_struct, int errorCase);

void	output_to_file(t_asm *champ);
void	format_file_output(int fd, char *champ);
char	*convert_int_to_hex(int num);


char	*make_header_string(t_header *header);

int 	check_for_command(char **line, t_asm *asm_struct, int start);

void	clean_labels_list(t_label **labels);

char	*get_trimmed_line(char **line,t_asm *asm_struct);


/*
 * Set champ's name and description
 */
void	get_champs_name(char *line, t_asm *asm_struct);
void	make_hex_name(char *hex_name, char *name);
void	get_champs_description(char *line, t_asm *asm_struct);
void	make_hex_description(char *hex_description, char *description);

t_com	*check_command(char *command);
t_com	*check_command_2(char *command);
t_com	*make_command_struct(char code, char codage, int label_size);

/*
 * Functions
 */
char	*get_label_name(char **tline);
char	*get_command_name(char **tline);
char	*cut_some_piece(char *line, unsigned int start);
t_label	*new_label_node(char *label_name);
void	push_label_front(t_label **labels, t_label *label);
void	push_command_front(t_com **commands, t_com *command);

int		is_comment(char **tline);

void	read_file(int fd, t_asm *asm_struct);
void	read_line(char **tline, t_asm *asm_struct);
size_t	read_dot_instruction(char **tline, size_t i, t_asm *asm_struct);
size_t	read_register(char **tline, size_t i, t_asm *asm_struct);
size_t	read_direct(char **tline, size_t i, t_asm *asm_struct);
size_t	read_indirect(char **tline, size_t i, t_asm *asm_struct);
size_t	read_string(char **tline, size_t i, t_asm *asm_struct);

int		check_register(char *tline, size_t i);

#endif
