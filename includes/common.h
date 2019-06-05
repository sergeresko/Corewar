/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 23:00:03 by vlvereta          #+#    #+#             */
/*   Updated: 2019/06/04 15:48:05 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <fcntl.h>
# include <stdio.h>
# include "../libft/includes/libft.h"

# define TRUE				1
# define FALSE				0

# define T_REG				1
# define T_DIR				2
# define T_IND				4

# define COREWAR_EXEC_MAGIC	0xea83f3

unsigned	parse_int(void const *buf);

#endif
