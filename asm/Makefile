# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#              #
#    Updated: 2019/05/31 18:42:25 by vlvereta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = asm

OBJ = asm.o \
    globals.o \
    read_dir.o \
    read_direct_label.o \
    read_dot_instr.o \
    read_indirect.o \
    read_indirect_label.o \
    read_register.o \
    read_string.o \
    asm_init_and_file_output.o \
    error_functions.o \
    functions.o \
    functions_2.o \
    functions_3.o \
    functions_5.o \
    make_name_and_description.o \
    check_command.o \
    helpers.o \
    check_argument.o \
    cleaning.o \
    hex_converters.o \
    dump_output.o \
    print_dump_output.o \
    print_commands.o \
    disassembler/disassembler.o \
    disassembler/init_and_getters.o \
    disassembler/read_args_and_code.o \
    disassembler/set_args_and_writers.o \
    ../common/read_headers.o \
    ../common/helpers_1.o \
    ../common/common_1.o

FLAGS = -Wall -Wextra -Werror

LIB_FOLDER = ../libft/

all: $(NAME)

$(NAME): $(OBJ)
	@	$(CC) -o $(NAME) $(OBJ) -L$(LIB_FOLDER) -lft

%.o: %.c
	@	$(CC) -o $@ -c $< -I./../includes

clean:
	@	rm -f $(OBJ)

fclean: clean
	@	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
