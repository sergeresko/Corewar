/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 18:23:24 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/20 18:23:26 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

const t_ops g_ops[16] = {
	{
		.name = "live",
		.opcode = 1,
		.args_amount = 1,
		.args_lst = {T_DIR, 0, 0},
		.s_tdir = 4,
		.args_ct = 0,
		.cycles = 10,
		.operation = &op_live
	},
	{
		.name = "ld",
		.opcode = 2,
		.args_amount = 2,
		.args_lst = {T_DIR | T_IND, T_REG, 0},
		.s_tdir = 4,
		.args_ct = 1,
		.cycles = 5,
		.operation = &op_ld
	},
	{
		.name = "st",
		.opcode = 3,
		.args_amount = 2,
		.args_lst = {T_REG, T_IND | T_REG, 0},
		.s_tdir = 4,
		.args_ct = 1,
		.cycles = 5,
		.operation = &op_st
	},
	{
		.name = "add",
		.opcode = 4,
		.args_amount = 3,
		.args_lst = {T_REG, T_REG, T_REG},
		.s_tdir = 4,
		.args_ct = 1,
		.cycles = 10,
		.operation = &op_add
	},
	{
		.name = "sub",
		.opcode = 5,
		.args_amount = 3,
		.args_lst = {T_REG, T_REG, T_REG},
		.s_tdir = 4,
		.args_ct = 1,
		.cycles = 10,
		.operation = &op_sub
	},
	{
		.name = "and",
		.opcode = 6,
		.args_amount = 3,
		.args_lst = {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG},
		.s_tdir = 4,
		.args_ct = 1,
		.cycles = 6,
		.operation = &op_and
	},
	{
		.name = "or",
		.opcode = 7,
		.args_amount = 3,
		.args_lst = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.s_tdir = 4,
		.args_ct = 1,
		.cycles = 6,
		.operation = &op_or
	},
	{
		.name = "xor",
		.opcode = 8,
		.args_amount = 3,
		.args_lst = {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG},
		.s_tdir = 4,
		.args_ct = 1,
		.cycles = 6,
		.operation = &op_xor
	},
	{
		.name = "zjmp",
		.opcode = 9,
		.args_amount = 1,
		.args_lst = {T_DIR, 0, 0},
		.s_tdir = 2,
		.args_ct = 0,
		.cycles = 20,
		.operation = &op_zjmp
	},
	{
		.name = "ldi",
		.opcode = 10,
		.args_amount = 3,
		.args_lst = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.s_tdir = 2,
		.args_ct = 1,
		.cycles = 25,
		.operation = &op_ldi
	},
	{
		.name = "sti",
		.opcode = 11,
		.args_amount = 3,
		.args_lst = {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG},
		.s_tdir = 2,
		.args_ct = 1,
		.cycles = 25,
		.operation = &op_sti
	},
	{
		.name = "fork",
		.opcode = 12,
		.args_amount = 1,
		.args_lst = {T_DIR, 0, 0},
		.s_tdir = 2,
		.args_ct = 0,
		.cycles = 800,
		.operation = &op_fork
	},
	{
		.name = "lld",
		.opcode = 13,
		.args_amount = 2,
		.args_lst = {T_DIR | T_IND, T_REG, 0},
		.s_tdir = 4,
		.args_ct = 1,
		.cycles = 10,
		.operation = &op_lld
	},
	{
		.name = "lldi",
		.opcode = 14,
		.args_amount = 3,
		.args_lst = {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG},
		.s_tdir = 2,
		.args_ct = 1,
		.cycles = 50,
		.operation = &op_lldi
	},
	{
		.name = "lfork",
		.opcode = 15,
		.args_amount = 1,
		.args_lst = {T_DIR, 0, 0},
		.s_tdir = 2,
		.args_ct = 0,
		.cycles = 1000,
		.operation = &op_lfork
	},
	{
		.name = "aff",
		.opcode = 16,
		.args_amount = 1,
		.args_lst = {T_REG, 0, 0},
		.s_tdir = 4,
		.args_ct = 1,
		.cycles = 2,
		.operation = &op_aff
	}
};
