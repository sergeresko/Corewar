/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/26 16:59:53 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "common.h"
# include "../libft/includes/libft.h"

typedef struct		s_player
{
	char 			*name;
	char 			*comment;
	int				size;
	void			*exec_code;
	int 			number;
	int 			fd;
	int 			self;
	const char 		*filename;
	struct s_player	*next;
}					t_player;

typedef struct		s_process
{
//	int				id;
	int				pc;
	int				carry;					// FALSE, t_bool
	unsigned		registers[REG_NUMBER];		// `uint32_t` or `char[4]`
	int				delay;					// 0
	int				cycle_when_last_live;	// 0
	char			op_code;		// byte
//	int				shift;
}					t_process;

typedef struct		s_vm
{										// initial values:
	t_player		*players;				// NULL
	int				nbr_players;			// 0
	int				is_dump;				// FALSE
	int				dump_cycles;			// -1
	char			arena[MEM_SIZE];		// zeroes and players' binary code
//	t_op			op[17];
	int				cycle;					// 0
	int				cycles_to_die;			// CYCLE_TO_DIE (1536)
	int				last_living_player;		// the largest player's id
	t_list			*processes;
	int				nbr_checks;				// 0
	int				nbr_live;				// 0 at the beginning of each round
}					t_vm;

void				check_arguments(t_vm *vm, int amount, char **args);
void				create_new_player(t_player **players, const char *arg, int *n);
void				push_player_back(t_player **players, t_player *player);
int					check_player_number(t_player **players, const char *self_name, int max, int number);
void				set_players_numbers(t_player *players, int counter);
void				clean_players_list(t_player **players);

/*
 * Helpers
 */
void                is_no_null_error(char *str, int i);

/*
 * Read and validation part
 */


/*
**
*/

void				perform_battle(t_vm *vm);

#endif
