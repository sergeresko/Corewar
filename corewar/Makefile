# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#              #
#    Updated: 2019/04/23 22:38:07 by vlvereta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

OBJ = corewar.o \
    errors.o

FLAGS = -Wall -Wextra - Werror

LIB_FOLDER = ../libft

all: $(NAME)

$(NAME): $(OBJ)
	@   $(CC) -o $(NAME) $(OBJ) -L$(LIB_FOLDER) -lft

%.o: %.c
	@	$(CC) -o $@ -c $< -I./../includes

clean:
	@	rm -f $(OBJ)

fclean: clean
	@	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
