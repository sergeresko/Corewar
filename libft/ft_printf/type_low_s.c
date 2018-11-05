/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_low_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:34:58 by vlvereta          #+#    #+#             */
/*   Updated: 2018/01/22 12:35:08 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		type_low_s(void *info)
{
	char	*s;
	t_info	*p;

	p = (t_info *)info;
	if (p->cur_flags->l)
		return (type_high_s(p));
	if (!(s = va_arg(p->ap, char *)))
		return (string_processing(p, "(null)", 6));
	return (string_processing(p, s, ft_strlen(s)));
}

int		string_processing(t_info *p, char *s, int len)
{
	char	*result;

	if (p->cur_flags->prec != -1 && p->cur_flags->prec < len)
	{
		if (!(result = ft_strsub(s, 0, p->cur_flags->prec)))
			return (-1);
		len = p->cur_flags->prec;
	}
	else if (!(result = ft_strdup(s)))
		return (-1);
	if ((len = width_for_string(p->cur_flags, &result, len)) == -1)
		return (clean_return(result, 0, 0, -1));
	string_to_output(p, result, len);
	return (1);
}

int		width_for_string(t_flags *flags, char **result, int len)
{
	int		last;
	char	*temp;

	if (flags->width > len)
	{
		if ((temp = ft_strnew(flags->width)))
		{
			if (flags->zero && !flags->left)
				ft_memset(temp, '0', flags->width);
			else
				ft_memset(temp, ' ', flags->width);
			last = flags->left ? len : flags->width;
			while (len)
				temp[--last] = (*result)[--len];
			free(*result);
			*result = temp;
			return (flags->width);
		}
		return (-1);
	}
	return (len);
}
