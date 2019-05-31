cmake_minimum_required(VERSION 3.12)
project(corewar C)

set(CMAKE_C_STANDARD 11)

include_directories(includes)
include_directories(libft/includes)

set(LIBFT
        libft/ft_printf/additional_types_or_flags.c
        libft/ft_printf/extra_functions.c
        libft/ft_printf/ft_printf.c
        libft/ft_printf/initialization.c
        libft/ft_printf/percent_and_co.c
        libft/ft_printf/type_di.c
        libft/ft_printf/type_high_c.c
        libft/ft_printf/type_high_s.c
        libft/ft_printf/type_low_s.c
        libft/ft_printf/type_pox.c
        libft/ft_printf/type_unsigned.c
        libft/get_next_line/get_next_line.c
        libft/includes/ft_printf.h
        libft/includes/get_next_line.h
        libft/includes/libft.h
        libft/srcs/ft_atoi.c
        libft/srcs/ft_bzero.c
        libft/srcs/ft_isalnum.c
        libft/srcs/ft_isalpha.c
        libft/srcs/ft_isascii.c
        libft/srcs/ft_isdigit.c
        libft/srcs/ft_islower.c
        libft/srcs/ft_isprint.c
        libft/srcs/ft_isupper.c
        libft/srcs/ft_itoa.c
        libft/srcs/ft_itoa_base.c
        libft/srcs/ft_lstadd.c
        libft/srcs/ft_lstdel.c
        libft/srcs/ft_lstdelone.c
        libft/srcs/ft_lstiter.c
        libft/srcs/ft_lstmap.c
        libft/srcs/ft_lstnew.c
        libft/srcs/ft_memalloc.c
        libft/srcs/ft_memccpy.c
        libft/srcs/ft_memchr.c
        libft/srcs/ft_memcmp.c
        libft/srcs/ft_memcpy.c
        libft/srcs/ft_memdel.c
        libft/srcs/ft_memmove.c
        libft/srcs/ft_memset.c
        libft/srcs/ft_putchar.c
        libft/srcs/ft_putchar_fd.c
        libft/srcs/ft_putendl.c
        libft/srcs/ft_putendl_fd.c
        libft/srcs/ft_putnbr.c
        libft/srcs/ft_putnbr_fd.c
        libft/srcs/ft_putstr.c
        libft/srcs/ft_putstr_fd.c
        libft/srcs/ft_strcat.c
        libft/srcs/ft_strchr.c
        libft/srcs/ft_strclr.c
        libft/srcs/ft_strcmp.c
        libft/srcs/ft_strcpy.c
        libft/srcs/ft_strdel.c
        libft/srcs/ft_strdup.c
        libft/srcs/ft_strequ.c
        libft/srcs/ft_striter.c
        libft/srcs/ft_striteri.c
        libft/srcs/ft_strjoin.c
        libft/srcs/ft_strlcat.c
        libft/srcs/ft_strlen.c
        libft/srcs/ft_strlower.c
        libft/srcs/ft_strmap.c
        libft/srcs/ft_strmapi.c
        libft/srcs/ft_strncat.c
        libft/srcs/ft_strncmp.c
        libft/srcs/ft_strncpy.c
        libft/srcs/ft_strnequ.c
        libft/srcs/ft_strnew.c
        libft/srcs/ft_strnstr.c
        libft/srcs/ft_strrchr.c
        libft/srcs/ft_strsplit.c
        libft/srcs/ft_strstr.c
        libft/srcs/ft_strsub.c
        libft/srcs/ft_strtrim.c
        libft/srcs/ft_strupper.c
        libft/srcs/ft_swap_bits32.c
        libft/srcs/ft_swap_bits64.c
        libft/srcs/ft_tolower.c
        libft/srcs/ft_toupper.c
        libft/srcs/is_only_digits.c
        libft/srcs/ft_atoi_base.c
        libft/srcs/ft_putchar_fd_wo_check.c
        libft/srcs/ft_get_substr_index.c)

add_executable(asm
        asm/asm.c
        asm/asm_init_and_file_output.c
        asm/functions.c
        asm/error_functions.c
        asm/make_name_and_description.c
        asm/check_command.c
        asm/check_argument.c
        asm/globals.c
        asm/helpers.c
        asm/cleaning.c
        asm/hex_converters.c
        asm/dump_output.c
        asm/disassembler/disassembler.c

        ${LIBFT} common/common_1.c common/read_headers.c common/helpers_1.c asm/disassembler/read_args_and_code.c asm/disassembler/init_and_getters.c asm/disassembler/set_args_and_writers.c asm/print_commands.c asm/read_dot_instr.c asm/read_register.c asm/read_dir.c asm/read_direct_label.c asm/read_indirect.c asm/read_indirect_label.c asm/read_string.c asm/functions_2.c asm/functions_3.c asm/functions_4.c asm/print_dump_output.c)

add_executable(corewar
        corewar/corewar.c
        corewar/errors.c
        corewar/vm.c

        ${LIBFT} common/common_1.c common/read_headers.c common/helpers_1.c)
