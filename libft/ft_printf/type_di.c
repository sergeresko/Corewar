/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_di.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 12:53:59 by vlvereta          #+#    #+#             */
/*   Updated: 2018/02/05 12:54:12 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		type_low_di(void *info)
{
	t_info		*p;
	long long	num;
	char		*result;

	p = (t_info *)info;
	if (p->cur_flags->z)
		num = va_arg(p->ap, ssize_t);
	else if (p->cur_flags->j)
		num = va_arg(p->ap, intmax_t);
	else if (p->cur_flags->ll)
		num = va_arg(p->ap, long long);
	else if (p->cur_flags->l)
		num = va_arg(p->ap, long);
	else if (p->cur_flags->h)
		num = (short)va_arg(p->ap, int);
	else if (p->cur_flags->hh)
		num = (char)va_arg(p->ap, int);
	else
		num = (int)va_arg(p->ap, int);
	if (!num && !p->cur_flags->prec)
		result = ft_strnew(0);
	else if (!(result = ft_itoa_base(num, 10)))
		return (-1);
	return (!check_flags_for_di(p, result) ? 0 : 1);
}

int		type_high_d(void *info)
{
	t_info	*p;

	p = (t_info *)info;
	p->cur_flags->l = 1;
	return (type_low_di(p));
}

int		check_flags_for_di(t_info *p, char *s)
{
	int		i;
	char	sign;
	char	*result;

	sign = 0;
	if (*s == '-' || p->cur_flags->space || p->cur_flags->sign)
	{
		sign = (*s == '-' ? '-' : sign);
		sign = (p->cur_flags->space && *s != '-' ? ' ' : sign);
		sign = (p->cur_flags->sign && *s != '-' ? '+' : sign);
	}
	result = (*s == '-' ? s + 1 : s);
	result = precision_for_di(p->cur_flags, result, sign);
	result = width_for_di(p->cur_flags, result, sign);
	if (sign)
	{
		i = 1;
		while (result[i] == ' ')
			i++;
		result[--i] = sign;
	}
	string_to_output(p, result, ft_strlen(result));
	return (1);
}

char	*precision_for_di(t_flags *flags, char *s, char sign)
{
	int		len;
	int		new_len;
	char	*result;

	len = ft_strlen(s);
	if (flags->prec > len && (result = ft_strnew(flags->prec)))
	{
		new_len = flags->prec;
		ft_memset(result, '0', new_len);
		while (len)
			result[--new_len] = s[--len];
		sign == '-' ? free(--s) : free(s);
		return (result);
	}
	else if (sign == '-')
	{
		result = ft_strdup(s);
		free(--s);
		return (result);
	}
	return (s);
}

char	*width_for_di(t_flags *flags, char *s, char sign)
{
	int		len;
	int		last;
	int		new_len;
	char	*result;

	len = (sign ? ft_strlen(s) + 1 : ft_strlen(s));
	new_len = (flags->width > len ? flags->width : len);
	if ((new_len > len || sign) && (result = ft_strnew(new_len)))
	{
		if (flags->zero && flags->prec == -1 && !flags->left)
			ft_memset(result, '0', new_len);
		else
			ft_memset(result, ' ', new_len);
		last = (flags->left ? len : new_len);
		len = (sign ? len - 1 : len);
		while (len)
			result[--last] = s[--len];
		free(s);
		return (result);
	}
	return (s);
}
