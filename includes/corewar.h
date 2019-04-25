/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/30 20:50:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/04/25 22:55:00 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include "errors.h"
# include "globals.h"
# include "../libft/includes/libft.h"

typedef struct		s_player
{
	char 			*name;
	char 			*comment;
	int 			number;
	int 			fd;
	const char 		*filename;
	struct s_player	*next;
}					t_player;

t_player			*check_arguments(int amount, char **args);
void				create_new_player(t_player **players, const char *arg, int number);
void				push_player_front(t_player **players, t_player *player);
int					check_player_number(t_player **players, int number);
int					set_player_number(t_player **players, int number);
void				clean_players_list(t_player **players);

#endif
