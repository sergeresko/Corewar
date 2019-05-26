/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 18:06:34 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "common.h"
# include "../libft/includes/libft.h"

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
	int				skipped_spaces;
	int				got_name;
	int				got_description;
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

void	clean_asm_struct(t_asm **asm_struct);
void	clean_commands_list(t_com **commands);

/*
 * Errors functions
 */
void	e__asm_initialization(void);
void	e__open_file(const char *name);
void	e__read_file(t_asm *asm_struct, int errorCase);

void	e__trim_line(const char *line);


void	output_to_file(t_asm *champ);
void	format_file_output(int fd, char *champ);


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
int		read_direct(char **tline, int i, t_com *command, t_asm *asm_struct);
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
void	print_real_value(t_com *command);
void	print_by_bytes(int arg, int bytes);
void	print_in_length(int length, char **str);
void	print_command_line(t_com *command, int index);
void	print_additional_command_line(t_com *command, int line, t_asm *ast_struct);

/*
 * Bonus part: Disassembler!
 */
void	disassemble_processing(int fd, const char *filename);
void	check_filename(const char *filename);
void	execution_code_processing(int new_file_fd, t_player *player);
void	player_initialization(t_player *player, int fd, const char *filename);
char	*get_filename_from_path(const char *filepath);
char	*get_command_name_by_code(int c);
void	get_args_types_by_codage(unsigned char c, t_com *command);
void	set_args_types(t_com *command);
int		create_new_file(t_player *player);
int 	read_args_by_types(char *code, int i, t_com *command);
int 	read_reg_by_type(const char *code, int i, t_com *command, int arg_num);
int 	read_dir_by_type(const char *code, int i, t_com *command, int arg_num);
int 	read_ind_by_type(const char *code, int i, t_com *command, int arg_num);
void	read_code(char *code, int length, int fd);
void	write_header(int fd, t_player *player);
void	write_args_to_file(int fd, t_com *command);
void	clean_split(char **split);

#endif
