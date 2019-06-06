/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   globals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/13 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 18:23:19 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int g_index = 0;

int g_dump_mode = FALSE;

int g_error_mode = FALSE;

const t_arg_type g_live[3][3] = {
	{T_DIR, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

const t_arg_type g_ld[3][3] = {
	{T_DIR, T_IND, 0},
	{T_REG, 0, 0},
	{0, 0, 0}
};

const t_arg_type g_st[3][3] = {
	{T_REG, 0, 0},
	{T_REG, T_IND, 0},
	{0, 0, 0}
};

const t_arg_type g_add[3][3] = {
	{T_REG, 0, 0},
	{T_REG, 0, 0},
	{T_REG, 0, 0}
};

const t_arg_type g_sub[3][3] = {
	{T_REG, 0, 0},
	{T_REG, 0, 0},
	{T_REG, 0, 0}
};

const t_arg_type g_and[3][3] = {
	{T_REG, T_DIR, T_IND},
	{T_REG, T_DIR, T_IND},
	{T_REG, 0, 0}
};

const t_arg_type g_or[3][3] = {
	{T_REG, T_DIR, T_IND},
	{T_REG, T_DIR, T_IND},
	{T_REG, 0, 0}
};

const t_arg_type g_xor[3][3] = {
	{T_REG, T_DIR, T_IND},
	{T_REG, T_DIR, T_IND},
	{T_REG, 0, 0}
};

const t_arg_type g_zjmp[3][3] = {
	{T_DIR, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

const t_arg_type g_ldi[3][3] = {
	{T_REG, T_DIR, T_IND},
	{T_REG, T_DIR, 0},
	{T_REG, 0, 0}
};

const t_arg_type g_sti[3][3] = {
	{T_REG, 0, 0},
	{T_REG, T_DIR, T_IND},
	{T_REG, T_DIR, 0}
};

const t_arg_type g_fork[3][3] = {
	{T_DIR, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};

const t_arg_type g_lld[3][3] = {
	{T_DIR, T_IND, 0},
	{T_REG, 0, 0},
	{0, 0, 0}
};

const t_arg_type g_lldi[3][3] = {
	{T_REG, T_DIR, T_IND},
	{T_REG, T_DIR, 0},
	{T_REG, 0, 0}
};

const t_arg_type g_lfork[3][3] = {
	{T_DIR, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};
const t_arg_type g_aff[3][3] = {
	{T_REG, 0, 0},
	{0, 0, 0},
	{0, 0, 0}
};
