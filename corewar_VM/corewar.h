/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdmytro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/16 20:38:28 by mdmytro           #+#    #+#             */
/*   Updated: 2019/02/16 20:38:32 by mdmytro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdint.h>
# include "op.h"

# define FLAG_SIZE		3
# define FILE_NAME_MAX	4096

enum {LIVE, LD, ST, ADD, SUB, AND, OR, XOR, ZJMOP, LDI, STI, FORK, LLD, LLDI, \
LFORK, AFF};

typedef struct			s_champion
{
	t_head				op;
	uint32_t			lives_num;
	uint32_t			true_lives_num;
	uint32_t			lust_live;
	int32_t				champs;
	int16_t				order;
	uint8_t				exec_code[CHAMP_MAX_SIZE];
	int8_t				name_file[FILE_NAME_MAX + 1];
	int32_t				fd;
	struct s_champion	*next;
}						t_champion;

typedef struct			s_champ_file
{
	t_chempion			*ch;
	int64_t				reserve;
	int8_t				flag[FLAG_SIZE];
	int8_t				flag_quant_ch[MAX_PLAYERS];
	uint32_t			count_ch;
	uint32_t			hand_brake;/*Forse to stop count champ files*/
}						t_champ_file;

typedef struct			s_vm_proc
{
	int8_t				carry;
	int8_t				is_alive;
	int32_t				pc;
	int32_t				reg[REG_NUMBER];
	int32_t				chemp_num;
	int16_t				cycle_exec;
	uint8_t				cmd;
	uint8_t				color;
	struct s_vm_proc	*next;
	struct s_vm_proc	*prev;
}						t_vm_proc;

typedef struct			s_operation
{
	void				(*f)(t_vm_proc *proc);
	short				cycle_value;
	char				label;
}						t_operation;

typedef struct			s_core
{
	t_champ_file		pd;
	t_vm_proc			*vp;
	t_operation			oper[16];
	uint32_t			cycle;
	int32_t				cycle_to_die;
	int32_t				check_ctd;
	uint32_t			identifi_max_check;
	uint32_t			proces_count;
	int32_t				rep_alive;
	int8_t				game_over;
}						t_core;

void					operation_initialize(void);
void					initialize(void);

void					st_add_champion(t_champion **ch);
void					st_reverse_champion(t_champion **ch);
void					st_free_champion(t_champion **ch);
int						st_reviwe_double_ch_num(t_champion *ch, int order);


#endif
