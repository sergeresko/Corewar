/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:23:24 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/27 15:11:42 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	The zeroth operation is there just so that indices coincide with opcodes:
**	(g_ops[k].opcode == k).
*/

t_op const		g_ops[17] = {
	{
		.name = NULL,
		.opcode = 0,
		.arg_amount = 0,
		.arg_list = {0, 0, 0},
		.dir_size = 0,
		.has_coding_byte = 0,
		.delay = 0,
		.operation = NULL,
	},
	{
		.name = "live",
		.opcode = 1,
		.arg_amount = 1,
		.arg_list = {T_DIR, 0, 0},
		.dir_size = 4,
		.has_coding_byte = FALSE,
		.delay = 10,
		.operation = &op_live,
	},
	{
		.name = "ld",
		.opcode = 2,
		.arg_amount = 2,
		.arg_list = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
		.has_coding_byte = TRUE,
		.delay = 5,
		.operation = &op_ld,
	},
	{
		.name = "st",
		.opcode = 3,
		.arg_amount = 2,
		.arg_list = {T_REG, T_IND | T_REG, 0},
		.dir_size = 4,
		.has_coding_byte = TRUE,
		.delay = 5,
		.operation = &op_st,
	},
	{
		.name = "add",
		.opcode = 4,
		.arg_amount = 3,
		.arg_list = {T_REG, T_REG, T_REG},
		.dir_size = 4,
		.has_coding_byte = TRUE,
		.delay = 10,
		.operation = &op_add,
	},
	{
		.name = "sub",
		.opcode = 5,
		.arg_amount = 3,
		.arg_list = {T_REG, T_REG, T_REG},
		.dir_size = 4,
		.has_coding_byte = TRUE,
		.delay = 10,
		.operation = &op_sub,
	},
	{
		.name = "and",
		.opcode = 6,
		.arg_amount = 3,
		.arg_list = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.dir_size = 4,
		.has_coding_byte = TRUE,
		.delay = 6,
		.operation = &op_and,
	},
	{
		.name = "or",
		.opcode = 7,
		.arg_amount = 3,
		.arg_list = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.dir_size = 4,
		.has_coding_byte = TRUE,
		.delay = 6,
		.operation = &op_or,
	},
	{
		.name = "xor",
		.opcode = 8,
		.arg_amount = 3,
		.arg_list = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.dir_size = 4,
		.has_coding_byte = TRUE,
		.delay = 6,
		.operation = &op_xor,
	},
	{
		.name = "zjmp",
		.opcode = 9,
		.arg_amount = 1,
		.arg_list = {T_DIR, 0, 0},
		.dir_size = 2,
		.has_coding_byte = FALSE,
		.delay = 20,
		.operation = &op_zjmp,
	},
	{
		.name = "ldi",
		.opcode = 10,
		.arg_amount = 3,
		.arg_list = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.dir_size = 2,
		.has_coding_byte = TRUE,
		.delay = 25,
		.operation = &op_ldi,
	},
	{
		.name = "sti",
		.opcode = 11,
		.arg_amount = 3,
		.arg_list = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.dir_size = 2,
		.has_coding_byte = TRUE,
		.delay = 25,
		.operation = &op_sti,
	},
	{
		.name = "fork",
		.opcode = 12,
		.arg_amount = 1,
		.arg_list = {T_DIR, 0, 0},
		.dir_size = 2,
		.has_coding_byte = FALSE,
		.delay = 800,
		.operation = &op_fork,
	},
	{
		.name = "lld",
		.opcode = 13,
		.arg_amount = 2,
		.arg_list = {T_DIR | T_IND, T_REG, 0},
		.dir_size = 4,
		.has_coding_byte = TRUE,
		.delay = 10,
		.operation = &op_lld,
	},
	{
		.name = "lldi",
		.opcode = 14,
		.arg_amount = 3,
		.arg_list = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.dir_size = 2,
		.has_coding_byte = TRUE,
		.delay = 50,
		.operation = &op_lldi,
	},
	{
		.name = "lfork",
		.opcode = 15,
		.arg_amount = 1,
		.arg_list = {T_DIR, 0, 0},
		.dir_size = 2,
		.has_coding_byte = FALSE,
		.delay = 1000,
		.operation = &op_lfork,
	},
	{
		.name = "aff",
		.opcode = 16,
		.arg_amount = 1,
		.arg_list = {T_REG, 0, 0},
		.dir_size = 4,
		.has_coding_byte = TRUE,
		.delay = 2,
		.operation = &op_aff,
	},
};
