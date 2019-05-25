/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_vm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:31:07 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 12:31:17 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_VM_H

# define OP_VM_H
# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE

# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3

# define MAX_ARGS_NUMBER		4
# define MAX_PLAYERS			4
# define MEM_SIZE				(4 * 1024)
# define IDX_MOD				(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

# define COMMENT_CHAR			'#'
# define ALT_COMMENT_CHAR		';'
# define LABEL_CHAR				':'
# define DIRECT_CHAR			'%'
# define SEPARATOR_CHAR			','

# define LABEL_CHARS			"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING		".name"
# define COMMENT_CMD_STRING		".comment"

# define REG_NUMBER				16

# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA			50
# define NBR_LIVE				21
# define MAX_CHECKS				10

typedef char					t_arg_type;

# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8

# define PROG_NAME_LENGTH		128
# define COMMENT_LENGTH			2048
# define COREWAR_EXEC_MAGIC		0xea83f3
# define MUS_PATH				"tunes/OUR_MUSIC_HERE.mp3"
# define CYCLES(k)				g_ops[k - 1].cycles
# define OPCODE(k)				g_ops[k - 1].opcode
# define S_TDIR(k)				g_ops[k - 1].s_tdir
# define ARGS_CT(k)				g_ops[k - 1].args_ct
# define ARGS_AMOUNT(k)			g_ops[k - 1].args_amount
# define ARG_LST(k, l)			g_ops[k - 1].args_lst[l]

#endif
