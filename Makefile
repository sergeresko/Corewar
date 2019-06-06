# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syeresko <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/04 16:16:51 by syeresko          #+#    #+#              #
#    Updated: 2019/06/06 15:29:36 by syeresko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM			=	asm
COREWAR		=	corewar
LIBFT		=	libft/libft.a

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

# --------- Header files ------------------------------------------------------

INC			=	$(addprefix inc/,					\
			  		common.h						\
					asm.h							\
					corewar.h						\
				)

# --------- Source files ------------------------------------------------------

SRC_COMMON	=	$(addprefix src/common/,			\
					parse_int.c						\
				)
SRC_ASM		=	$(addprefix src/asm/,				\
					asm.c							\
					asm_init_and_file_output.c		\
					check_argument.c				\
					check_command.c					\
					cleaning.c						\
					cook_l_arg.c					\
					dump_output.c					\
					error_functions.c				\
					functions.c						\
					functions_2.c					\
					functions_3.c					\
					functions_4.c					\
					get_champs_description.c		\
					get_champs_name.c				\
					get_error_code.c				\
					globals.c						\
					helpers.c						\
					hex_converters.c				\
					long_name_and_desc_error.c		\
					make_hex_name_and_desc.c		\
					make_name_desc_functions.c		\
					make_name_desc_functions_2.c	\
					print_commands.c				\
					print_dump_output.c				\
					print_errors.c					\
					read_dir.c						\
					read_direct_label.c				\
					read_dot_instr.c				\
					read_indir.c					\
					read_indirect_label.c			\
					read_register.c					\
					read_string.c					\
					$(addprefix disassembler/,		\
						disassembler.c				\
						init_and_getters.c			\
						read_args_and_code.c		\
						read_header.c				\
						set_args_and_writers.c		\
					)								\
				)
SRC_COREWAR	=	$(addprefix src/corewar/,			\
					advance_car.c					\
					announce_winner.c				\
					champ_colors.c					\
					clone_car.c						\
					corewar.c						\
					create_car.c					\
					dump_memory.c					\
					error.c							\
					execute_operation.c				\
					get_arg_size.c					\
					get_champ_by_id.c				\
					get_opt_bonus.c					\
					get_opt_champs.c				\
					get_opt_dump.c					\
					get_reg.c						\
					get_value.c						\
					interactive_get.c				\
					list.c							\
					load_champs.c					\
					op_add.c						\
					op_aff.c						\
					op_and.c						\
					op_fork.c						\
					op_ld.c							\
					op_ldi.c						\
					op_lfork.c						\
					op_live.c						\
					op_lld.c						\
					op_lldi.c						\
					op_or.c							\
					op_st.c							\
					op_sti.c						\
					op_sub.c						\
					op_xor.c						\
					op_zjmp.c						\
					operations.c					\
					perform_battle.c				\
					perform_check.c					\
					perform_cycle.c					\
					perform_round.c					\
					read_champ_header.c				\
					read_champs.c					\
					read_from_field.c				\
					set_champ_ids.c					\
					show_usage.c					\
					write_to_field.c				\
				)

# --------- Object files ------------------------------------------------------

OBJ_ASM		=	$(patsubst src/%.c, obj/%.o,		\
					$(SRC_COMMON)					\
					$(SRC_ASM)						\
				)
OBJ_COREWAR	=	$(patsubst src/%.c, obj/%.o,		\
					$(SRC_COMMON)					\
					$(SRC_COREWAR)					\
				)

# --------- Phony targets -----------------------------------------------------

.PHONY: all clean fclean re

all: $(LIBFT) $(ASM) $(COREWAR)

clean:
	@ rm -f $(OBJ_ASM) $(OBJ_COREWAR)
	@ make clean -sC libft/

fclean: clean
	@ rm -rf obj/
	@ rm -f $(ASM) $(COREWAR)
	@ make fclean -sC libft/

re: fclean all

# --------- Linking -----------------------------------------------------------

$(ASM): $(OBJ_ASM) $(LIBFT)
	@ mkdir -p obj/
	@ printf "%-60s\n" "Linking $@"
	@ $(CC) $(CFLAGS) $(OBJ_ASM) $(LIBFT) -o $(ASM)
	@ echo "Done"

$(COREWAR): $(OBJ_COREWAR) $(LIBFT)
	@ mkdir -p obj/
	@ printf "%-60s\n" "Linking $@"
	@ $(CC) $(CFLAGS) $(OBJ_COREWAR) $(LIBFT) -o $(COREWAR)
	@ echo "Done"

$(LIBFT):
	@ echo "Building $@"
	@ make -sC libft/
	@ echo "Done"

# --------- Compiling ---------------------------------------------------------

obj/%.o: src/%.c $(INC)
	@ mkdir -p $(dir $@)
	@ printf "%-60s\r" "Compiling $<"
	@ $(CC) $(CFLAGS) -c $< -I inc/ -I libft/includes -o $@
