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
# include "globals.h"
# include "../libft/includes/libft.h"

#define TRUE 1
#define FALSE 0
# define BYTE 8

typedef struct		s_header
{
	unsigned int	size;
	char			name[NAME_LENGTH + 1];
	char 			description[DESC_LENGTH + 1];
	char			hex_name[HEX_NAME_LENGTH + 1];
	char			hex_description[HEX_DESC_LENGTH + 1];
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
	int				errorCase;
	int				skippedLine;
}					t_data;

typedef struct		s_com
{
	char			code;
	char 			*name;
	int 			length;
	int 			index;
	int 			is_codage;
	unsigned char	codage;
	t_arg_type		arg_types[3];
	int				arguments[3];
	char 			*arg_labels[3];
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
	char 			*champion;
	char 			*filename;

}					t_asm;

int		asm_init(t_asm **asm_struct, const char *argv);
char	*get_filename(const char *argv);
void	file_processing(int fd, const char *argv);

int		get_substr_index(const char *big, const char *little);
void	clean_asm_struct(t_asm **asm_struct);
void	clean_commands_list(t_com **commands);

/*
 * Errors functions
 */
void	e__args_amount(void);
void	e__asm_initialization(void);
void	e__open_file(const char *name);
void	e__read_file(void);
void	e__trim_line(const char *line);


void	output_to_file(t_asm *champ);
void	format_file_output(int fd, char *champ);
char	*convert_int_to_hex(int num);


char	*make_header_string(t_header *header);


void	clean_labels_list(t_label **labels);

char	*get_trimmed_line(char **line,t_asm *asm_struct);


int		includes(const char *str, char c);

/*
 * Set champ's name and description
 */
void	get_champs_name(char *line, t_asm *asm_struct);
void	make_hex_name(char *hex_name, char *name);
void	get_champs_description(char *line, t_asm *asm_struct);
void	make_hex_description(char *hex_description, char *description);

t_com	*check_command(char *command);
t_com	*check_command_2(char *command);
t_com	*make_command_struct(char *name, char code, char codage, int label_size);
void	check_command_line(t_asm *asm_struct);
/*
 * Functions
 */
void	push_label_front(t_label **labels, t_label *label);
void	push_command_front(t_com **commands, t_com *command);

void	read_file(int fd, t_asm *asm_struct);
void	read_line_1(char **tline, t_asm *asm_struct);
size_t 	read_line_2(char **tline, size_t i, t_asm *asm_struct);
size_t	read_dot_instruction(char **tline, size_t i, t_asm *asm_struct);
size_t	read_register(char **tline, size_t i, t_com *command);
int		read_direct(char **tline, int i, t_com *command);
int		read_direct_label(char **tline, int i, t_com *command);
int		read_indirect(char **tline, int i, t_com *command);
int		read_indirect_label(char **tline, int i, t_com *command);
size_t	read_string(char **tline, size_t i, t_asm *asm_struct);
void	read_label(char *tline, size_t start, size_t end, t_asm *asm_struct);
void	read_command(char *tline, size_t start, size_t end, t_asm *asm_struct);
int		check_label(char *tline, int end, int check_label_char);
int 	is_register(char *tline, size_t i);

int 	get_argument_number(t_com *command);
int 	check_argument_1(char *command, int arg_num, t_arg_type arg_type);
int 	check_argument_2(char *command, int arg_num, t_arg_type arg_type);
int 	is_argument_possible(const t_arg_type arg_types[], t_arg_type arg_type);
void	write_argument(t_com *command, int arg_num, t_arg_type arg_type, int argument);
void	write_label_argument(t_com *command, int arg_num, t_arg_type arg_type, char **label);

char	make_codage(t_com *command);
int 	command_length(t_com *command);
char	*byte_in_bits(char c);
int 	check_proper_ending(const char *line, int i);

void	cook_champion(t_asm *asm_struct);
void	cook_command(t_com *command, int i, t_asm *asm_struct);
int		cook_argument(t_com *command, int arg_num, int index, t_asm *asm_struct);
int 	cook_label_argument(t_com *command, int arg_num, int index, t_asm *asm_struct);
int 	get_label_index(t_label *labels, char *label_name);
char	*get_label_name(t_label *labels, int index);
char	*byte_in_hex(unsigned char c);
char	*short_in_hex(unsigned short s);
char	*integer_in_hex(unsigned int num);
char	*get_revert_integer(t_com *command, int arg_num, int delta);


void	dump_output(t_asm *asm_struct);
void	rush_through_commands(t_com *command, int index, t_asm *asm_struct);
void	print_in_length(int length, char **str);
void	print_command_line(t_com *command, int index);
void	print_additional_command_line(t_com *command, int line);

#endif
