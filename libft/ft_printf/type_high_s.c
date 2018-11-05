/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_high_s.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:34:58 by vlvereta          #+#    #+#             */
/*   Updated: 2018/01/22 12:35:08 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		type_high_s(void *info)
{
	int		len;
	wchar_t	*s;
	t_info	*p;
	char	*result;

	p = (t_info *)info;
	if (!(s = va_arg(p->ap, wchar_t *)))
		return (string_processing(p, "(null)", 6));
	if ((len = read_unistring(p->cur_flags->prec, s, &result)) == -1)
		return (clean_return(result, 0, 0, -1));
	if ((len = width_for_unistring(p->cur_flags, &result, len)) == -1)
		return (clean_return(result, 0, 0, -1));
	string_to_output(p, result, len);
	return (1);
}

int		read_unistring(int precision, wchar_t *s, char **result)
{
	int		len;
	int		ulen;
	char	*unichar;

	len = 0;
	*result = ft_strnew(len);
	if (!(unichar = ft_strnew(4)))
		return (-1);
	while (*s)
	{
		if (!(ulen = *s < 128 ? 1 : wchar_encoder(*s, &unichar)))
			return (clean_return(unichar, 0, 0, -1));
		if (ulen == 1)
			*unichar = *s;
		if (precision != -1 && precision < (len + ulen))
			break ;
		len = add_unichar(result, len, unichar, ulen);
		ft_bzero(unichar, 4);
		s++;
	}
	free(unichar);
	return (len);
}

int		add_unichar(char **result, int len, char *unichar, int ulen)
{
	int		i;
	int		j;
	int		new_len;
	char	*temp;

	new_len = len + ulen;
	if ((temp = ft_strnew(new_len)))
	{
		i = 0;
		j = 0;
		while (i < len)
			temp[j++] = (*result)[i++];
		free(*result);
		i = 0;
		while (i < ulen)
			temp[j++] = unichar[i++];
		*result = temp;
		return (new_len);
	}
	return (len);
}

int		width_for_unistring(t_flags *flags, char **result, int len)
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
