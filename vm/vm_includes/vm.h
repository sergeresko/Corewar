/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 12:31:22 by omaiko            #+#    #+#             */
/*   Updated: 2019/05/25 12:31:24 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "../libft/libft.h"
/*# include "SDL.h"
# include "SDL_mixer.h"
# include <ncurses.h>*/ //for_music_and_visual_part
# include <fcntl.h>
# include "op_vm.h"

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
	int				num;
	unsigned int	exec_amount;
	unsigned int	ongoing_lives;
	unsigned int	recent_cycle;
	unsigned char	*exec_code;
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
}				t_champ;

typedef struct	s_field
{
	unsigned char	square;
	int				color;
	int				sup_colour;
	int				cycles;
}				t_field;

typedef struct	s_car
{
	int					num;
	int					carry;
	int					opcode;
	int					now_live;
	int					arg_class[3];
	int					op_cycles_to_move;
	int					recent_cycle;
	int					args_nbr;
	int					regs[REG_NUMBER + 1];
	t_champ				*prev;
	unsigned int		place;
	struct s_car		*then;
}				t_car;

typedef struct	s_cw
{
	t_ind			*ind;
	t_champ			champ[4];
	t_champ			*last_champ;
	t_field			field[MEM_SIZE];
	t_car			*car;
	unsigned int	amount_of_alives[4];
	int				tune_on;
	int				x;
	int				y;
	int				ac;
	int				fd;
	int				c_per_sec; // for_visual
	int				ongoing_cycle;
	int				running; // pause_or_run_for_visual
	int				champs_amount;
	int				carry_nbr;
	int				alive_carry_nbr;
	int				scan_cycle;
	int				ctd;
	int				alive_nbr;
	int				scan_nbr;
	int				free_num[5];
	char			**av;
	char			*fail_sense;
}				t_cw;

typedef struct	s_ops
{
	char	*name;
	int		opcode;
	int		args_amount;
	int		args_lst[3];
	int		s_tdir;
	int		args_ct;
	int		cycles;
	void	(*operation)(t_cw *, t_car *);
}				t_ops;

void			show_usage(t_cw *data);
void			fail(t_cw *data);
void			fail_sense(t_cw *data, char *sense);
void			output_result(t_cw *cw);

/*int				scan_args_ct(t_cw *cw, t_car *car);
int				scan_regs(t_cw *cw, t_car *car);*/
int				take_amount_by_class(t_car *car, int i);
unsigned int	take_arg_from_field(t_field *field, unsigned int plc, int size);
int				take_arg_by_class(t_cw *cw, t_car *car, int indicator);
int				take_arg_place(t_car *car, int indicator);
void			rewrite_field(t_cw *cw, t_car *carr, int amount, int addr);

void			op_live(t_cw *cw, t_car *car);
void			op_zjmp(t_cw *cw, t_car *car);
void			op_and(t_cw *cw, t_car *car);
void			op_add(t_cw *cw, t_car *car);
void			op_sub(t_cw *cw, t_car *car);
void			op_ld(t_cw *cw, t_car *car);
void			op_or(t_cw *cw, t_car *car);
void			op_xor(t_cw *cw, t_car *car);
void			op_st(t_cw *cw, t_car *car);
void			op_ldi(t_cw *cw, t_car *car);
void			op_sti(t_cw *cw, t_car *car);
void			op_fork(t_cw *cw, t_car *car);
void			op_lfork(t_cw *cw, t_car *car);
void			op_lld(t_cw *cw, t_car *car);
void			op_lldi(t_cw *cw, t_car *car);
void			op_aff(t_cw *cw, t_car *car);

#endif
