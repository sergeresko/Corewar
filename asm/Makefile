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

OBJ = srcs/asm.o

FLAGS = -Wall -Wextra -Werror

LIBFT = make -C $(LIB_FOLDER)

LIB_FOLDER = ../libft/

all: $(NAME)

$(NAME): $(OBJ)
	@	$(LIBFT)
	@	$(CC) -o $(NAME) $(OBJ) -L$(LIB_FOLDER) -lft

%.o: %.c
	@	$(CC) -o $@ -c $< -Iincludes $(FLAGS)

clean:
	@	make -C $(LIB_FOLDER) clean
	@	rm -f $(OBJ)

fclean: clean
	@	make -C $(LIB_FOLDER) fclean
	@	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
