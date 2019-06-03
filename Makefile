# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/03 20:50:03 by vlvereta          #+#    #+#              #
#    Updated: 2019/06/03 08:01:35 by vlvereta         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_DIR = ./libft/
ASM_DIR = ./asm/
COREVAR_DIR = ./corewar/

all: 
	make -C $(LIBFT_DIR)
	make -C $(ASM_DIR)
	make -C $(COREVAR_DIR)

clean:
	make -C $(LIBFT_DIR) clean
	make -C $(ASM_DIR) clean
	make -C $(COREVAR_DIR) clean

fclean:
	make -C $(LIBFT_DIR) fclean
	make -C $(ASM_DIR) fclean
	make -C $(COREVAR_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
