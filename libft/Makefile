# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/25 14:17:49 by vlvereta          #+#    #+#              #
#    Updated: 2019/05/28 20:12:07 by syeresko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libft.a

FLAGS = -Wall -Wextra -Werror

OBJ = $(addprefix srcs/, \
		ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o \
		ft_isascii.o ft_isdigit.o ft_islower.o ft_isprint.o \
		ft_isupper.o ft_itoa.o ft_itoa_base.o ft_itoa_base_for_hex.o ft_lstadd.o \
		ft_lstdel.o ft_lstdelone.o ft_lstiter.o ft_lstmap.o \
		ft_lstnew.o ft_memalloc.o ft_memccpy.o ft_memchr.o \
		ft_memcmp.o ft_memcpy.o ft_memdel.o ft_memmove.o \
		ft_memset.o ft_putchar.o ft_putchar_fd.o ft_putendl.o \
		ft_putendl_fd.o ft_putnbr.o ft_putnbr_fd.o \
		ft_putstr.o ft_putstr_fd.o ft_strcat.o \
		ft_strchr.o ft_strclr.o ft_strcmp.o ft_strcpy.o \
		ft_strdel.o ft_strdup.o ft_strequ.o ft_striter.o \
		ft_striteri.o ft_strjoin.o ft_strlcat.o ft_strlen.o \
		ft_strmap.o ft_strmapi.o ft_strncat.o ft_strncmp.o \
		ft_strncpy.o ft_strnequ.o ft_strnew.o ft_strnstr.o \
		ft_strrchr.o ft_strsplit.o ft_strstr.o ft_strsub.o \
		ft_strtrim.o ft_tolower.o ft_strlower.o \
		ft_toupper.o ft_strupper.o is_only_digits.o \
		ft_swap_bits32.o ft_swap_bits64.o ft_get_substr_index.o \
		ft_atoi_base.o ft_putchar_fd_wo_check.o \
	) \
	$(addprefix get_next_line/, \
		get_next_line.o \
	) \
	$(addprefix ft_printf/, \
		ft_min.o ft_max.o ft_abs.o ft_putnchar.o \
		ft_floor_l.o ft_utf8_len.o ft_parse_number.o \
		ft_printf.o \
		pf_parse_format.o pf_converters.o pf_count_zeroes.o \
		pf_print_alpha.o pf_print_signed.o pf_print_unsigned.o \
		pf_print_pointer.o pf_print_float.o \
	)

HEADER = ./includes/libft.h
HEADER_GNL = ./includes/get_next_line.h
HEADER_PRINTF = ./includes/ft_printf.h

all: $(NAME)

$(NAME): $(OBJ)
	@	ar rc $(NAME) $(OBJ)
	@	ranlib $(NAME)

%.o: %.c $(HEADER) $(HEADER_GNL) $(HEADER_PRINTF)
	@	$(CC) -o $@ -c $< -I includes $(FLAGS)

clean:
	@	rm -f $(OBJ)

fclean: clean
	@	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
