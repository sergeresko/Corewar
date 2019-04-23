/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/04/13 20:50:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOBALS_H
# define GLOBALS_H

# include "asm.h"

/*
 * Current index and size of the champion
 */
extern int g_index;

/*
 * Dumping annotated mode
 */
extern int g_dump_mode;

/*
 * Global error mode for reading
 */
extern int g_error_mode;

/*
 * Commands' arguments list
 */
extern const t_arg_type LIVE[3][3];
extern const t_arg_type LD[3][3];
extern const t_arg_type ST[3][3];
extern const t_arg_type ADD[3][3];
extern const t_arg_type SUB[3][3];
extern const t_arg_type AND[3][3];
extern const t_arg_type OR[3][3];
extern const t_arg_type XOR[3][3];
extern const t_arg_type ZJMP[3][3];
extern const t_arg_type LDI[3][3];
extern const t_arg_type STI[3][3];
extern const t_arg_type FORK[3][3];
extern const t_arg_type LLD[3][3];
extern const t_arg_type LLDI[3][3];
extern const t_arg_type LFORK[3][3];
extern const t_arg_type AFF[3][3];

#endif
