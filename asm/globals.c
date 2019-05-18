/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/14 23:11:19 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
 * Current index and size of the champion
 */
int g_index = 0;

/*
 * Dumping annotated mode
 */
int g_dump_mode = FALSE;

/*
 * Global error mode for reading
 */
int g_error_mode = FALSE;

/*
 * Commands' arguments list
 */
const t_arg_type LIVE[3][3] = {{T_DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}};
const t_arg_type LD[3][3] = {{T_DIR, T_IND, 0}, {T_REG, 0, 0}, {0, 0, 0}};
const t_arg_type ST[3][3] = {{T_REG, 0, 0}, {T_REG, T_IND, 0}, {0, 0, 0}};
const t_arg_type ADD[3][3] = {{T_REG, 0, 0}, {T_REG, 0, 0}, {T_REG, 0, 0}};
const t_arg_type SUB[3][3] = {{T_REG, 0, 0}, {T_REG, 0, 0}, {T_REG, 0, 0}};
const t_arg_type AND[3][3] = {{T_REG, T_DIR, T_IND}, {T_REG, T_DIR, T_IND}, {T_REG, 0, 0}};
const t_arg_type OR[3][3] = {{T_REG, T_DIR, T_IND}, {T_REG, T_DIR, T_IND}, {T_REG, 0, 0}};
const t_arg_type XOR[3][3] = {{T_REG, T_DIR, T_IND}, {T_REG, T_DIR, T_IND}, {T_REG, 0, 0}};
const t_arg_type ZJMP[3][3] = {{T_DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}};
const t_arg_type LDI[3][3] = {{T_REG, T_DIR, T_IND}, {T_REG, T_DIR, 0}, {T_REG, 0, 0}};
const t_arg_type STI[3][3] = {{T_REG, 0, 0}, {T_REG, T_DIR, T_IND}, {T_REG, T_DIR, 0}};
const t_arg_type FORK[3][3] = {{T_DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}};
const t_arg_type LLD[3][3] = {{T_DIR, T_IND, 0}, {T_REG, 0, 0}, {0, 0, 0}};
const t_arg_type LLDI[3][3] = {{T_REG, T_DIR, T_IND}, {T_REG, T_DIR, 0}, {T_REG, 0, 0}};
const t_arg_type LFORK[3][3] = {{T_DIR, 0, 0}, {0, 0, 0}, {0, 0, 0}};
const t_arg_type AFF[3][3] = {{T_REG, 0, 0}, {0, 0, 0}, {0, 0, 0}};
