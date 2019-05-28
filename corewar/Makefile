# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#              #
#    Updated: 2019/05/28 18:16:05 by syeresko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

OBJ = corewar.o \
	  get_opt_dump.o \
	  get_opt_champs.o \
	  set_champ_ids.o \
	  read_champ_header.o \
	  read_champs.o \
	  throw_error.o \
	  perror_exit.o \
	  list.o \
	  ../common/helpers_1.o

#OBJ = corewar.o \
#	errors.o \
#	../common/read_headers.o \
#	../common/helpers_1.o \
#	../common/common_1.o \
#	vm.o

FLAGS = -Wall -Wextra -Werror

LIB_FOLDER = ../libft

all: $(NAME)

$(NAME): $(OBJ)
	@   $(CC) $(FLAGS) -o $(NAME) $(OBJ) -L$(LIB_FOLDER) -lft

%.o: %.c
	@	$(CC) $(FLAGS) -o $@ -c $< -I../includes

clean:
	@	rm -f $(OBJ)

fclean: clean
	@	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
