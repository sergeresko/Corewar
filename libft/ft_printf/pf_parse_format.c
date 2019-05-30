/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pf_parse_format.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:57:37 by syeresko          #+#    #+#             */
/*   Updated: 2018/12/09 19:46:30 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**		pf_parse_flags
*/

static void	pf_parse_flags(t_fmt *f, const char **a_str)
{
	char		c;

	while ((c = **a_str))
	{
		if (c == '#')
			f->alt = 1;
		else if (c == '0')
			f->zero = 1;
		else if (c == '-')
			f->left = 1;
		else if (c == ' ')
			f->blank = 1;
		else if (c == '+')
			f->plus = 1;
		else if (c == '\'')
			f->group = 1;
		else
			break ;
		++(*a_str);
	}
}

/*
**		pf_parse_width
**	Sets .width (and possibly .left) field to the value
**	specified in the initial portion of string *a_str
**	and shifts the pointer to the next character after the specification.
**	If the argument passed through '*' is negative, .left is set
**	and .width is set to the absolute value of the argument.
**	If no width is specified, .width isn't modified (default 0).
*/

static void	pf_parse_width(t_fmt *f, const char **a_str, va_list ap)
{
	int			width;

	if (**a_str == '*')
	{
		width = va_arg(ap, int);
		++(*a_str);
	}
	else
		width = ft_parse_number(a_str);
	if (width >= 0)
		f->width = width;
	else
	{
		f->left = 1;
		f->width = -width;
	}
}

/*
**		pf_parse_precision
**	Sets .prec field to the value specified in the initial portion
**	of string *a_str
**	and shifts the pointer to the next character after the specification.
**	If the specification doesn't start with '.', .prec is set to -1.
**	If the number after '.' is missing or if the agrument
**	passed through '*' is negative, .prec is set to 0.
**	TODO: update description.
*/

static void	pf_parse_precision(t_fmt *f, const char **a_str, va_list ap)
{
	int			precision;

	if (**a_str == '*')
	{
		precision = va_arg(ap, int);
		f->prec = (precision < 0) ? PF_PREC_NONE : precision;
		++(*a_str);
	}
	else
	{
		precision = ft_parse_number(a_str);
		f->prec = (precision < 0) ? 0 : precision;
	}
}

/*
**		pf_parse_modifier
**	Sets .mod field to the LAST value specified in the initial portion
**	of string *a_str
**	and shifts the pointer to the next chararcter after the specification.
**	A specification is considered a sequence of any length composed of "hlL".
**	Examples:
**		hlh  ->  MOD_H
**		llhL ->  MOD_L_CAPITAL
**		Lhh  ->  MOD_HH
*/

static void	pf_parse_modifier(t_fmt *f, const char **a_str)
{
	char		c;
	t_modifier	m;

	while (1)
	{
		c = **a_str;
		m = f->mod;
		if (c == 'h')
			f->mod = (m == MOD_H || m == MOD_HH) ? MOD_HH : MOD_H;
		else if (c == 'l')
			f->mod = (m == MOD_L || m == MOD_LL) ? MOD_LL : MOD_L;
		else if (c == 'j')
			f->mod = MOD_J;
		else if (c == 'z')
			f->mod = MOD_Z;
		else if (c == 'L')
			f->mod = MOD_L_CAPITAL;
		else
			break ;
		++(*a_str);
	}
}

/*
**		pf_parse_format
**	TODO
*/

void		pf_parse_format(t_fmt *a_fmt, const char **a_str, va_list ap)
{
	char		c;

	ft_bzero(a_fmt, sizeof(t_fmt));
	a_fmt->prec = PF_PREC_NONE;
	while ((c = **a_str) && !(a_fmt->conv))
	{
		if (ft_strchr(PF_FLAGS, c))
			pf_parse_flags(a_fmt, a_str);
		else if (ft_isdigit(c) || c == '*')
			pf_parse_width(a_fmt, a_str, ap);
		else if (c == '.')
		{
			++(*a_str);
			pf_parse_precision(a_fmt, a_str, ap);
		}
		else if (ft_strchr(PF_MODIFIERS, c))
			pf_parse_modifier(a_fmt, a_str);
		else
		{
			if (ft_strchr(PF_CONVERSIONS, c))
				a_fmt->conv = c;
			++(*a_str);
		}
	}
}
