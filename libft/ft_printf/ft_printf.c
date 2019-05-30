/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 17:21:58 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/09 20:05:29 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include <inttypes.h>
#include <wchar.h>
#include "libft.h"

/*
**		pf_print_plain
**	Prints the initial portion of string *a_str to stdout until '\0' or '%'
**	is encountered, shifts the pointer to this stop-character
**	and returns the number of printed characters.
*/

static int			pf_print_plain(const char **a_str)
{
	const char	*s;
	int			len;

	s = *a_str;
	len = 0;
	while (s[len] && s[len] != '%')
		++len;
	if (len)
		write(1, s, len);
	*a_str += len;
	return (len);
}

static intmax_t		get_arg_signed(const t_fmt *f, va_list ap)
{
	if (f->mod == MOD_HH)
		return ((char)va_arg(ap, int));
	if (f->mod == MOD_H)
		return ((short)va_arg(ap, int));
	if (f->mod == MOD_L)
		return (va_arg(ap, long));
	if (f->mod == MOD_LL)
		return (va_arg(ap, long long));
	if (f->mod == MOD_J)
		return (va_arg(ap, intmax_t));
	if (f->mod == MOD_Z)
		return (va_arg(ap, ssize_t));
	return (va_arg(ap, int));
}

static uintmax_t	get_arg_unsigned(const t_fmt *f, va_list ap)
{
	if (f->mod == MOD_HH)
		return ((unsigned char)va_arg(ap, unsigned));
	if (f->mod == MOD_H)
		return ((unsigned short)va_arg(ap, unsigned));
	if (f->mod == MOD_L)
		return (va_arg(ap, unsigned long));
	if (f->mod == MOD_LL)
		return (va_arg(ap, unsigned long long));
	if (f->mod == MOD_J)
		return (va_arg(ap, uintmax_t));
	if (f->mod == MOD_Z)
		return (va_arg(ap, size_t));
	return (va_arg(ap, unsigned));
}

/*
**		pf_print_formatted
*/

static int			pf_print_formatted(const char **a_str, va_list ap)
{
	t_fmt		fmt;

	pf_parse_format(&fmt, a_str, ap);
	if (fmt.conv && ft_strchr("cs%", fmt.conv))
		return (pf_print_alpha(&fmt, ap));
	if (fmt.conv && ft_strchr("di", fmt.conv))
		return (pf_print_signed(&fmt, get_arg_signed(&fmt, ap)));
	if (fmt.conv && ft_strchr("uoxXbB", fmt.conv))
		return (pf_print_unsigned(&fmt, get_arg_unsigned(&fmt, ap)));
	if (fmt.conv == 'p')
		return (pf_print_pointer(&fmt, va_arg(ap, void *)));
	if (fmt.conv == 'f' && fmt.mod == MOD_L_CAPITAL)
		return (pf_print_float(&fmt, va_arg(ap, long double)));
	if (fmt.conv == 'f')
		return (pf_print_float(&fmt, va_arg(ap, double)));
	return (0);
}

/*
**	ft_printf
*/

int					ft_printf(const char *format, ...)
{
	va_list		ap;
	int			len;

	va_start(ap, format);
	len = 0;
	while (1)
	{
		len += pf_print_plain(&format);
		if (*format == '\0')
			break ;
		++format;
		len += pf_print_formatted(&format, ap);
	}
	va_end(ap);
	return (len);
}
