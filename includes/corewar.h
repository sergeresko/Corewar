/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:31:22 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/30 15:05:31 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "common.h"
# include "../libft/includes/libft.h"

//# include "SDL.h"
//# include "SDL_mixer.h"
//# include <ncurses.h>		// for_music_and_visual_part
//# include <fcntl.h>		// ?

// not used:
typedef struct	s_ind
{
	int	u;
	int l;
	int	c;
	int v;
	int	t;
	int	n;
	int	dump;
	int	dump_amount;
	int	dump_bytes;
	/*int	lives;
	int	cycles;
	int	ops;
	int	deaths;
	int	actions;*/ //levels_of_detalisation
}				t_ind;

typedef struct	s_champ
{
	int		id;
	char	*filename;
	char	*name;//name[PROG_NAME_LENGTH + 1];
	char	*comment;//comment[COMMENT_LENGTH + 1];
	int		size;
	char	*exec_code;			// char * ?
//	unsigned int	ongoing_lives;
//	unsigned int	recent_cycle;
}				t_champ;

typedef struct	s_field
{
	unsigned char	square;
//	int				color;
//	int				sup_color;
//	int				cycles;
}				t_field;

typedef struct	s_car
{
	int		id;
	int		regs[REG_NUMBER + 1];	// + dummy `regs[0]`
	int		carry;
	unsigned	place;		// pc
//	int		now_live;
	int		opcode;
	int		arg_amount;
	int		arg_class[3];
	int		arg_place[3];
	int		offset;
//	int		op_cycles_to_move;		// delay
	int		delay;
//	int		recent_cycle;			// cycle_when_last_live
	int		cycle_when_last_live;
//	t_champ	*prev;
//	struct s_car		*then;
}				t_car;

typedef struct	s_vm
{										// initial values:
	int				help;					// FALSE
	int				verbose;				// FALSE
	int				color;					// FALSE
	int				dump_cycle;				// -1
	int				dump_bytes;				// uninitialized (or maybe 32 ?)
//	t_ind			*ind;
	t_field			field[MEM_SIZE];		// zeroes and players' executable code
	int				cycle;					// 0
	int				cycle_to_die;			// CYCLE_TO_DIE (1536)
	int				last_living_champ_id;	// the largest player's id (or maybe 0 ?)
	int				champ_amount;			// 0
	t_list			*champs;				// NULL
	t_list			*cars;					// NULL
	int				nbr_checks;				// 0
	int				nbr_live;				// 0 at the beginning of each round
}				t_vm;

/*
**
*/

void			list_push(t_list **head, void *content);
void			list_push_back(t_list **head, void *content);
void			*list_pop(t_list **head);

char			**get_opt_bonus(t_vm *vm, char **av);
char			**get_opt_dump(t_vm *vm, char **av);
void			get_opt_champs(t_vm *vm, char **av);
void			set_champ_ids(t_list *champs, int champ_amount);
void			read_champ_header(int fd, t_champ *champ);
void			read_champs(t_list *champs);

t_champ			*get_champ_by_id(t_list *champs, int champ_id);

void			throw_error(char const *message);
void			perror_exit(char const *prefix);

void			perform_battle(t_vm *vm);

t_car			*create_car();
t_car			*clone_car(t_car const *car, int place);

void			execute_operation(t_vm *vm, t_car *car);
int				get_arg_size(t_car const *car, int arg);



// not used:
typedef struct	s_cw
{
	t_ind			*ind;
	t_champ			champ[4];
	t_champ			*last_champ;
	t_field			field[MEM_SIZE];
	t_car			*car;
	unsigned int	amount_of_alives[4];
//	int				tune_on;
//	int				x;
//	int				y;
	int				ac;
	int				fd;
//	int				c_per_sec; // for_visual
	int				ongoing_cycle;
//	int				running; // pause_or_run_for_visual
	int				champs_amount;
	int				carry_nbr;
	int				alive_carry_nbr;
	int				scan_cycle;
	int				ctd;	// cycle_do_die
	int				alive_nbr;
	int				scan_nbr;
	int				free_num[5];
	char			**av;
	char			*fail_sense;
}				t_cw;

typedef struct	s_op
{
	char	*name;
	int		opcode;
	int		arg_amount;
	int		arg_list[3];
	int		dir_size;
	int		has_coding_byte;
	int		delay;
	void	(*operation)(t_vm *, t_car *);
}				t_op;

extern t_op const	g_ops[17];




// not used:
void			show_usage(t_cw *data);
void			fail(t_cw *data);
void			fail_sense(t_cw *data, char *sense);
void			output_result(t_cw *cw);

/*int				scan_args_ct(t_cw *cw, t_car *car);
int				scan_regs(t_cw *cw, t_car *car);*/

//int				take_amount_by_class(t_car *car, int i);
//unsigned int	take_arg_from_field(t_field *field, unsigned int plc, int size);
//int				take_arg_by_class(t_cw *cw, t_car *car, int indicator);
//int				take_arg_place(t_car *car, int indicator);
//void			rewrite_field(t_cw *cw, t_car *carr, int amount, int addr);

unsigned		read_from_field(t_field const *field, unsigned place, int size);
void			write_to_field(t_field *field, unsigned place, unsigned value);

int				get_value(t_vm const *vm, t_car const *car, int arg);
uint8_t			get_reg(t_vm const *vm, t_car const *car, int arg);

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

#endif
