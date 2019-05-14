/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/05/14 23:01:15 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "op.h"
# include "common.h"
# include "errors.h"
# include "globals.h"
# include "../libft/includes/libft.h"

typedef struct		s_player
{
	char 			*name;
	char 			*comment;
	int				size;
	int 			number;
	int 			fd;
	int 			self;
	const char 		*filename;
	struct s_player	*next;
}					t_player;

t_player			*check_arguments(int amount, char **args);
void				create_new_player(t_player **players, const char *arg, int *n);
void				push_player_back(t_player **players, t_player *player);
int					check_player_number(t_player **players, const char *self_name, int max, int number);
void				set_players_numbers(t_player *players, int counter);
void				clean_players_list(t_player **players);

/*
 * Helpers
 */
char				*clean_from_whitespaces(char *str);

/*
 * Read and validation part
 */
void				read_headers(t_player *players);
void				check_magic(char *header);

#endif
