# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#              #
#    Updated: 2018/09/30 20:50:32 by vlvereta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = asm

OBJ = asm.o \
    globals.o \
    asm_init.o \
    error_functions.o \
    functions.o \
    make_file_output.o \
    make_name_and_description.o \
    check_command.o \
    helpers.o \
    check_argument.o

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
