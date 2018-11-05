/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_unsigned.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 13:57:12 by vlvereta          #+#    #+#             */
/*   Updated: 2018/02/05 13:57:29 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		type_low_u(void *info)
{
	t_info				*p;
	unsigned long long	num;
	char				*result;

	p = (t_info *)info;
	if (!(num = to_unsigned(p)) && !p->cur_flags->prec)
		result = ft_strnew(0);
	else if (!(result = llu_base(num, 10)))
		return (-1);
	check_flags_for_oux(p->cur_flags, &result, 'u');
	string_to_output(p, result, ft_strlen(result));
	return (1);
}

int		type_high_u(void *info)
{
	t_info	*p;

	p = (t_info *)info;
	p->cur_flags->l = 1;
	return (type_low_u(p));
}

void	check_flags_for_oux(t_flags *flags, char **str, char type)
{
	int		i;
	char	*result;

	result = *str;
	result = precision_for_oux(flags, result);
	if (flags->hash && type == 'o' && *result != '0')
	{
		i = 1;
		result = width_for_oux(flags, result, 1);
		while (result[i] == ' ')
			i++;
		result[--i] = '0';
	}
	else if (flags->hash && type == 'x')
	{
		result = width_for_oux(flags, result, 2);
		i = (result[0] == '0' ? 2 : 1);
		while (result[i] == ' ')
			i++;
		result[--i] = 'x';
		result[--i] = '0';
	}
	else
		result = width_for_oux(flags, result, 0);
	*str = result;
}

char	*precision_for_oux(t_flags *flags, char *str)
{
	int		len;
	int		new_len;
	char	*result;

	len = ft_strlen(str);
	if (flags->prec > len && (result = ft_strnew(flags->prec)))
	{
		new_len = flags->prec;
		ft_memset(result, '0', new_len);
		while (len)
			result[--new_len] = str[--len];
		free(str);
		return (result);
	}
	return (str);
}

char	*width_for_oux(t_flags *flags, char *str, int extra_len)
{
	int		len;
	int		last;
	int		new_len;
	char	*result;

	len = ft_strlen(str) + extra_len;
	new_len = (flags->width > len ? flags->width : len);
	if ((new_len > len || extra_len) && (result = ft_strnew(new_len)))
	{
		if (flags->zero && flags->prec == -1 && !flags->left)
			ft_memset(result, '0', new_len);
		else
			ft_memset(result, ' ', new_len);
		last = (flags->left ? len : new_len);
		len = (extra_len ? len - extra_len : len);
		while (len)
			result[--last] = str[--len];
		free(str);
		return (result);
	}
	return (str);
}
