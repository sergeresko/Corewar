/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:33:27 by zaz               #+#    #+#             */
/*   Updated: 2013/11/06 14:21:46 by zaz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define ASM_USAGE "Usage: ./asm [-a] <sourcefile.s>\n    -a : Instead of creating a .cor file, outputs a stripped and annotated version of the code to the standard output"
# define ASM_INITIALIZATION_ERROR "Asm initialization failed"

# define COR_USAGE "Usage: ./corewar [-d N -s N -v N | -b --stealth | -n --stealth] [-a] <champion1.cor> <...>\n    -a        : Prints output from \"aff\" (Default is to hide it)"

# define OPEN_FILE_ERROR "Can't read source file "
# define READ_FILE_ERROR "Cannot read file"
# define TRIM_LINE_ERROR "Something went wrong while trimming a line: "

void	exit_with_usage(void);
void    e__args_amount(void);
void	e__open_file(const char *name);

#endif
