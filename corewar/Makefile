# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#              #
#    Updated: 2019/06/01 15:02:53 by syeresko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

OBJ = corewar.o \
	  get_opt_bonus.o get_opt_dump.o get_opt_champs.o \
	  set_champ_ids.o \
	  read_champ_header.o read_champs.o \
	  get_champ_by_id.o \
	  error.o \
	  show_usage.o \
	  list.o \
	  ../common/helpers_1.o \
	  \
	  operations.o \
	  op_live.o \
	  op_ld.o op_ldi.o op_lld.o op_lldi.o \
	  op_st.o op_sti.o \
	  op_add.o op_sub.o \
	  op_and.o op_or.o op_xor.o \
	  op_zjmp.o \
	  op_fork.o op_lfork.o \
	  op_aff.o \
	  \
	  get_reg.o get_value.o \
	  read_from_field.o write_to_field.o \
	  \
	  execute_operation.o get_arg_size.o \
	  advance_car.o \
	  create_car.o clone_car.o \
	  load_champs.o announce_winner.o dump_memory.o \
	  interactive_get.o \
	  perform_cycle.o perform_check.o perform_round.o perform_battle.o

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
