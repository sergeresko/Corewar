/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/03 14:04:34 by vlvereta         ###   ########.fr       */
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
	char			description[DESC_LENGTH + 1];
	char			hex_name[HEX_NAME_LENGTH + 1];
	char			hex_description[HEX_DESC_LENGTH + 1];
}					t_header;

typedef struct		s_label
{
	int				index;
	char			*name;
	struct s_label	*next;
}					t_label;

typedef struct		s_data
{
	int				line;
	int				row;
	int				error_case;
	int				skipped_line;
	int				skipped_spaces;
	int				got_name;
	int				got_description;
}					t_data;

typedef struct		s_com
{
	char			code;
	char			*name;
	int				length;
	int				index;
	int				is_codage;
	unsigned char	codage;
	t_arg_type		arg_types[3];
	int				arguments[3];
	char			*arg_labels[3];
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
	char			*champion;
	char			*filename;

}					t_asm;

char				*convert_int_to_hex(int num);
int					asm_init(t_asm **asm_struct, const char *argv);
char				*get_filename(const char *argv);
void				file_processing(int fd, const char *argv);
void				clean_asm_struct(t_asm **asm_struct);
void				clean_commands_list(t_com **commands);
void				e__asm_initialization(void);
void				e__open_file(const char *name);
void				e__read_file(t_asm *asm_struct, int error_case);
void				e__trim_line(const char *line);
void				output_to_file(t_asm *champ);
void				format_file_output(int fd, char *champ);
char				*make_header_string(t_header *header);
void				clean_labels_list(t_label **labels);
char				*get_trimmed_line(char **line, t_asm *asm_struct);
int					includes(const char *str, char c);
void				get_champs_name(char *line, t_asm *asm_struct);
void				make_hex_name(char *hex_name, char *name);
void				get_champs_description(char *line, t_asm *asm_struct);
void				make_hex_desc(char *hex_description, char *description);
t_com				*check_command(char *command);
t_com				*check_command_2(char *command);
t_com				*make_com_struct(char *n, char code, char codg, int l_size);
void				check_command_line(t_asm *asm_struct);
void				push_label_front(t_label **labels, t_label *label);
void				push_command_front(t_com **commands, t_com *command);
void				read_file(int fd, t_asm *asm_struct);
void				read_line_1(char **tline, t_asm *asm_struct);
size_t				read_line_2(char **tline, size_t i);
size_t				read_dot_instr(char **tline, size_t i, t_asm *asm_struct);
size_t				read_register(char **tline, size_t i, t_com *command);
int					read_dir(char **tl, int i, t_com *com);
int					read_direct_label(char **tline, int i, t_com *command);
int					read_indirect(char **tline, int i, t_com *command);
int					read_indirect_label(char **tline, int i, t_com *command);
size_t				read_string(char **tline, size_t i, t_asm *asm_struct);
void				read_label(char *tl, size_t st, size_t end, t_asm *asm_str);
void				read_com(char *tl, size_t st, size_t end, t_asm *asm_str);
void				read_com_2(char *n, t_com *com, t_asm *asm_str);
int					check_label(char *tline, int end, int check_label_char);
int					is_register(char *tline, size_t i);
int					get_argument_number(t_com *command);
int					check_arg_1(char *com, int a_n, t_arg_type a_t);
int					check_arg_2(char *com, int a_n, t_arg_type a_t);
int					is_arg(const t_arg_type *arg_ts, t_arg_type arg_t);
void				write_arg(t_com *com, int a_n, t_arg_type a_t, int arg);
void				write_l_a(t_com *com, int a_n, t_arg_type a_t, char **l);
char				make_codage(t_com *command);
int					command_length(t_com *command);
char				*byte_in_bits(char c);
int					check_proper_ending(const char *line, int i);
void				cook_champion(t_asm *asm_struct);
void				cook_command(t_com *command, int i, t_asm *asm_struct);
int					cook_arg(t_com *com, int a_n, int index, t_asm *asm_str);
int					cook_l_arg(t_com *com, int a_n, int index, t_asm *asm_str);
int					get_label_index(t_label *labels, char *label_name);
char				*get_label_name(t_label *labels, int index);
char				*byte_in_hex(unsigned char c);
char				*short_in_hex(unsigned short s);
char				*integer_in_hex(unsigned int num);
char				*get_revert_integer(t_com *command, int arg_num, int delta);
void				dump_output(t_asm *asm_struct);
void				rush_through_com(t_com *com, int index, t_asm *asm_str);
void				print_by_bytes(int arg, int bytes);
void				print_in_length(int length, char **str);
void				print_command_line(t_com *command, int index);
void				print_command_line_loop(t_com *command, int i, char *temp);
void				print_add_com_line_1(t_com *com, int line, t_asm *ast_str);
int					print_add_com_line_2(t_com *com, int i, int line, int label_arg);
int 				print_add_com_line_3(t_com *com, int line, int label_arg);

void				disassemble_processing(int fd, const char *filename);
void				check_filename(const char *filename);
void				exec_code_proc(int new_file_fd, t_player *player);
void				player_init(t_player *pl, int fd, const char *file);
char				*get_filename_from_path(const char *filepath);
char				*get_command_name_by_code(int c);
void				get_args_types_by_codage(unsigned char c, t_com *command);
void				set_args_types(t_com *command);
int					create_new_file(t_player *player);
int					read_args_by_types(char *code, int i, t_com *command);
int					read_reg_byt(const char *code, int i, t_com *com, int a_n);
int					read_dir_byt(const char *code, int i, t_com *com, int a_n);
int					read_ind_byt(const char *code, int i, t_com *com, int a_n);
void				read_code(char *code, int length, int fd);
void				write_header(int fd, t_player *player);
void				write_args_to_file(int fd, t_com *command);
void				clean_split(char **split);
void				check_instruction(char *eline, t_asm *asm_struct, int i);
void				check_register(char *eline, t_asm *asm_struct, int i);
void				check_direct_label(char *eline, t_asm *asm_struct, int i);
int					ft_nbr_lngth(long n);
void				check_lexical(t_asm *asm_struct, int i);
void				check_commands(char *eline, t_asm *asm_struct, int i);
int					check_for_letters(char *eline);
void				check_for_symbols(char *eline, t_asm *asm_struct, int i);
void				check_indirect(char *eline, t_asm *asm_struct, int i);
void				check_direct(char *eline, t_asm *asm_struct, int i);
void				get_error_code(char *line, t_asm *asm_struct, int i);
void				check_colon(char *eline, t_asm *asm_struct, int i);
void				print_label_error(t_com *com, int a_n);

#endif
