/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_pox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:48:56 by vlvereta          #+#    #+#             */
/*   Updated: 2018/02/05 13:49:09 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		type_p(void *info)
{
	t_info	*p;
	void	*ptr;
	char	*result;

	p = (t_info *)info;
	if (!(ptr = va_arg(p->ap, void *)) && !p->cur_flags->prec)
		result = ft_strnew(0);
	else if (!(result = llu_base((unsigned long long)ptr, 16)))
		return (-1);
	p->cur_flags->hash = 1;
	check_flags_for_oux(p->cur_flags, &result, 'x');
	string_to_output(p, result, ft_strlen(result));
	return (1);
}

int		type_low_o(void *info)
{
	t_info				*p;
	unsigned long long	num;
	char				*result;

	p = (t_info *)info;
	if (!(num = to_unsigned(p)) && !p->cur_flags->prec && !p->cur_flags->hash)
		result = ft_strnew(0);
	else if (!(result = llu_base(num, 8)))
		return (-1);
	if (!num && p->cur_flags->hash)
		p->cur_flags->hash = 0;
	check_flags_for_oux(p->cur_flags, &result, 'o');
	string_to_output(p, result, ft_strlen(result));
	return (1);
}

int		type_high_o(void *info)
{
	t_info	*p;

	p = (t_info *)info;
	p->cur_flags->l = 1;
	return (type_low_o(p));
}

int		type_low_x(void *info)
{
	t_info				*p;
	unsigned long long	num;
	char				*result;

	p = (t_info *)info;
	if (!(num = to_unsigned(p)) && !p->cur_flags->prec)
		result = ft_strnew(0);
	else if (!(result = llu_base(num, 16)))
		return (-1);
	if (!num && p->cur_flags->hash)
		p->cur_flags->hash = 0;
	check_flags_for_oux(p->cur_flags, &result, 'x');
	string_to_output(p, result, ft_strlen(result));
	return (1);
}

int		type_high_x(void *info)
{
	int					i;
	t_info				*p;
	unsigned long long	num;
	char				*result;

	p = (t_info *)info;
	if (!(num = to_unsigned(p)) && !p->cur_flags->prec)
		result = ft_strnew(0);
	else if (!(result = llu_base(num, 16)))
		return (-1);
	if (!num && p->cur_flags->hash)
		p->cur_flags->hash = 0;
	check_flags_for_oux(p->cur_flags, &result, 'x');
	i = 0;
	while (result[i])
	{
		if (ft_islower(result[i]))
			result[i] = ft_toupper(result[i]);
		i++;
	}
	string_to_output(p, result, ft_strlen(result));
	return (1);
}
