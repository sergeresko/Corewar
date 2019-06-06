/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:31:22 by omaiko            #+#    #+#             */
/*   Updated: 2019/06/04 15:44:20 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "common.h"

# define IND_SIZE		2
# define MAX_PLAYERS	4

# define MEM_SIZE		(4 * 1024)
# define IDX_MOD		(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE	(MEM_SIZE / 6)

# define REG_NUMBER		16

# define CYCLE_TO_DIE	1536
# define CYCLE_DELTA	50
# define NBR_LIVE		21
# define MAX_CHECKS		10

# define LEAKS_COMMAND	"leaks -q corewar >&2"

/*
**	a champion
*/

typedef struct	s_champ
{
	int				id;
	char			*filename;
	char			*name;
	char			*comment;
	int				size;
	char			*exec_code;
}				t_champ;

t_champ			*get_champ_by_id(t_list *champs, int champ_id);

/*
**	ANSI sequences for colors associated with champions
*/

extern char *const	g_champ_colors[5];

/*
**	the memory of the virtual machine
**
**	`champ_id` is used for colored dumps.
*/

typedef struct	s_field
{
	unsigned char	square;
	int				champ_id;
}				t_field;

/*
**	a process
**
**	`regs[0]` is a dummy register existing solely in order to make it possible
**	to refer to registers by their actual numbers (i.e. `r1` is `regs[1]`).
**
**	`place` is PC.
**
**	`opcode` and all fields after it hold information about the operation
**	the process is going to execute.
*/

typedef struct	s_car
{
	int				id;
	int				champ_id;
	int				regs[REG_NUMBER + 1];
	int				carry;
	unsigned		place;
	int				cycle_when_last_live;
	int				opcode;
	int				arg_amount;
	int				arg_class[3];
	int				arg_place[3];
	unsigned		offset;
	int				delay;
}				t_car;

t_car			*create_car(void);
t_car			*clone_car(t_car const *car, unsigned place);

/*
**	boolean options of the virtual machine (initially all FALSE)
*/

typedef struct	s_opt
{
	int				help;
	int				verbose;
	int				silent;
	int				canonic;
	int				color;
	int				leaks;
}				t_opt;

/*
**	the virtual machine
**
**	`interactive_cycle` is the number of the cycle after which a prompt
**	is to be displayed in the interactive mode; in order to indicate that
**	the interactive mode is off, `interactive_cycle` is set to (-1).
**
**	`dump_cycle` is the number of the cycle at the end of which the memory
**	is to be dumped and the battle terminated; similarly, if the dump should
**	not be made, `dump_cycle` is set to (-1).
**
**	`dump_bytes` indicates how many bytes per line are to be printed
**	in the dump.
*/

typedef struct	s_vm
{
	int				champ_amount;
	t_list			*champs;
	int				last_living_champ_id;
	t_list			*cars;
	t_field			field[MEM_SIZE];
	int				cycle;
	int				cycle_to_die;
	int				nbr_checks;
	int				nbr_live;
	t_opt			opt;
	int				interactive_cycle;
	int				dump_cycle;
	int				dump_bytes;
}				t_vm;

/*
**	handling command-line arguments
*/

char			**get_opt_bonus(t_vm *vm, char **av);
char			**get_opt_dump(t_vm *vm, char **av);
void			get_opt_champs(t_vm *vm, char **av);

void			set_champ_ids(t_list *champs, int champ_amount);
void			read_champ_header(int fd, t_champ *champ);
void			read_champs(t_list *champs);

/*
**	the core engine of the virtual machine
*/

void			load_champs(t_vm *vm);
void			announce_winner(t_vm const *vm);

void			dump_memory(t_vm const *vm, int dump_bytes);

void			interactive_get(t_vm *vm);

void			perform_cycle(t_vm *vm);
void			perform_check(t_vm *vm);
void			perform_round(t_vm *vm);
void			perform_battle(t_vm *vm);

void			execute_operation(t_vm *vm, t_car *car);
void			advance_car(t_vm const *vm, t_car *car);

/*
**	operations
*/

typedef struct	s_op
{
	char			*name;
	int				opcode;
	int				arg_amount;
	int				arg_list[3];
	int				dir_size;
	int				has_coding_byte;
	int				delay;
	void			(*operation)(t_vm *, t_car *);
}				t_op;

extern t_op const	g_ops[17];

int				get_arg_size(t_car const *car, int arg);

void			op_live(t_vm *vm, t_car *car);
void			op_zjmp(t_vm *vm, t_car *car);
void			op_and(t_vm *vm, t_car *car);
void			op_add(t_vm *vm, t_car *car);
void			op_sub(t_vm *vm, t_car *car);
void			op_ld(t_vm *vm, t_car *car);
void			op_or(t_vm *vm, t_car *car);
void			op_xor(t_vm *vm, t_car *car);
void			op_st(t_vm *vm, t_car *car);
void			op_ldi(t_vm *vm, t_car *car);
void			op_sti(t_vm *vm, t_car *car);
void			op_fork(t_vm *vm, t_car *car);
void			op_lfork(t_vm *vm, t_car *car);
void			op_lld(t_vm *vm, t_car *car);
void			op_lldi(t_vm *vm, t_car *car);
void			op_aff(t_vm *vm, t_car *car);

/*
**	reading and writing for processes
*/

unsigned		read_from_field(t_field const *field, unsigned place, int size);
void			write_to_field(t_field *field,
								t_car const *car, int address, unsigned value);

int				get_value(t_vm const *vm, t_car const *car, int arg);
unsigned char	get_reg(t_vm const *vm, t_car const *car, int arg);

/*
**	list functions
*/

void			list_push(t_list **head, void *content);
void			list_push_back(t_list **head, void *content);
void			*list_pop(t_list **head);

/*
**	error functions
*/

void			fatal_error(char const *message);
void			perror_exit(char const *prefix);
void			show_usage(t_vm const *vm);

#endif
