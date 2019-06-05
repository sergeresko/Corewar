# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#              #
#    Updated: 2019/06/03 13:38:29 by vlvereta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = asm

OBJ = asm.o \
	asm_init_and_file_output.o \
	check_argument.o \
	check_command.o \
	cleaning.o \
	cook_l_arg.o \
	dump_output.o \
	error_functions.o \
	functions.o \
	functions_2.o \
	functions_3.o \
	functions_4.o \
	get_error_code.o \
    globals.o \
    helpers.o \
    hex_converters.o \
    make_description.o \
    make_name_and_description.o \
    make_name_desc_functions.o \
    make_name_desc_functions_2.o \
    print_commands.o \
    print_dump_output.o \
    print_errors.o \
    read_dir.o \
    read_direct_label.o \
    read_dot_instr.o \
    read_indirect.o \
    read_indirect_label.o \
    read_register.o \
    read_string.o \
    disassembler/disassembler.o \
    disassembler/init_and_getters.o \
    disassembler/read_args_and_code.o \
    disassembler/read_header.o \
    disassembler/set_args_and_writers.o \
    ../common/parse_int.o

FLAGS = -Wall -Wextra -Werror

LIB_FOLDER = ../libft/

all: $(NAME)

$(NAME): $(OBJ)
	@	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -L$(LIB_FOLDER) -lft

%.o: %.c
	@	$(CC) $(FLAGS) -o $@ -c $< -I./../includes

clean:
	@	rm -f $(OBJ)

fclean: clean
	@	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
