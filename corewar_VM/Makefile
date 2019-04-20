# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdmytro <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/18 13:55:42 by mdmytro           #+#    #+#              #
#    Updated: 2019/03/18 13:55:43 by mdmytro          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	corewar
FLAGS		= 	-Wall -Werror -Wextra
CC			=	gcc

DIR_INC		=	./includes/
DIR_SRC		=	./source/

DIR_OBJ		=	./obj/
DIR_LIB		=	./libft/
DIR_LIB_INC	=	$(DIR_LIB)includes/
LIBFT		=	$(DIR_LIB)libft.a

HEAD_CW		=	op.h
HEAD_VM		=	corewar.h

#------------------Source-----------------------
C_VM		=	initialize.c operation_initialize.c parce_file.c\
				incom_arguments.c

OBJ			=	$(addprefix $(DIR_OBJ), $(C_VM:.c=.o))

INC			=	$(addprefix -I, $(DIR_INC) $(DIR_LIB_INC))
INC_VM		=	$(addprefix $(DIR_INC), $(HEAD_VM) $(HEAD_CW))



all: $(DIR_LIB)libft.a $(NAME)

$(DIR_LIB)libft.a:
		@make -C $(DIR_LIB)

#----------------------------- Compil Block ------------------------------
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) -o $(NAME) $(OBJ) $(LIBFT)
	@echo "Compiling@ [ $(NAME) ]

#source
$(DIR_OBJ)%.o: $(DIR_SRC)%.c $(INC_VM)
	@mkdir -p $(DIR_OBJ)
	@$(CC) $(FLAGS) $(INC) -c -o $@ $<
	@echo "Linking" [ $< ]

clean:
	@make -C $(DIR_LIB) clean
	@rm -rf $(DIR_OBJ)
	@echo "Clean [ obj files ft_ssl ]"

fclean:
	@make -C $(DIR_LIB) fclean
	@rm -rf $(DIR_OBJ)
	@echo "Clean [ obj files ft_ssl ]"
	@rm -f $(NAME)
	@echo "Clean" [ $(NAME) ]

re: fclean all

.PHONY: all clean fclean re
