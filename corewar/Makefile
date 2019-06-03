# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#              #
#    Updated: 2019/06/03 08:08:26 by vlvereta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

OBJ = corewar.o \
    errors.o \
	../common/read_header.o \
	../common/read_header_helpers.o \
	vm.o

FLAGS = -Wall -Wextra -Werror

LIB_FOLDER = ../libft

all: $(NAME)

$(NAME): $(OBJ)
	@   $(CC) -o $(NAME) $(OBJ) -L$(LIB_FOLDER) -lft

%.o: %.c
	@	$(CC) $(FLAGS) -o $@ -c $< -I../includes

clean:
	@	rm -f $(OBJ)

fclean: clean
	@	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
