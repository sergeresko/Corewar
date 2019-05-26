/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 15:32:17 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/26 15:35:58 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//include

uint8_t		get_arg_size(t_car const *car, int k)
{
	uint8_t const	class = car->arg_class[k];

	if (class == T_DIR)
	{
		return (g_ops[car->opcode].dir_size);
	}
	if (class == T_IND)
	{
		return (IND_SIZE);
	}
	if (class == T_REG)
	{
		return (1);
	}
	return (0);					// ?
}
