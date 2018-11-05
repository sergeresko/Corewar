/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 23:15:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/02/01 23:18:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	int		i;
	t_info	p;

	if (!start_initialization(&p))
		return (-1);
	va_start(p.ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if ((i = read_flags((char **)(&format), &p)) != -1)
				p.type_handlers[i](&p);
			else
				continue ;
		}
		else
			char_to_output(&p, *format);
		flags_to_null(p.cur_flags);
		format++;
	}
	write(1, p.output, p.outlen);
	va_end(p.ap);
	return (clean_return(p.cur_flags, p.output, 0, !p.error ? p.outlen : -1));
}

int		read_flags(char **format, t_info *p)
{
	int		i;

	while (**format)
	{
		i = 0;
		while (i < AMOUNT)
			if (**format == p->types[i++])
				return (--i);
		if (**format == '-')
			p->cur_flags->left = 1;
		else if (**format == '+')
			p->cur_flags->sign = 1;
		else if (**format == ' ')
			p->cur_flags->space = 1;
		else if (**format == '#')
			p->cur_flags->hash = 1;
		else if (**format == '0')
			p->cur_flags->zero = 1;
		else if (!read_width(format, p))
			break ;
		(*format)++;
	}
	return (-1);
}

int		read_width(char **format, t_info *p)
{
	int		t;

	if (ft_isdigit(**format))
	{
		p->cur_flags->width = ft_atoi(*format);
		while (ft_isdigit(**format))
			(*format)++;
		(*format)--;
	}
	else if (**format == '*')
	{
		if ((t = va_arg(p->ap, int)) < 0)
		{
			p->cur_flags->width = -t;
			p->cur_flags->left = 1;
		}
		else
			p->cur_flags->width = t;
	}
	else if (**format == '.')
		read_precision(format, p);
	else
		return (read_size(format, p) ? 1 : 0);
	return (1);
}

void	read_precision(char **format, t_info *p)
{
	int		t;
	char	*temp;

	temp = *format + 1;
	if (ft_isdigit(*temp))
	{
		p->cur_flags->prec = ft_atoi(temp);
		while (ft_isdigit(*temp))
			temp++;
		*format = --temp;
	}
	else if (*temp == '*')
	{
		t = va_arg(p->ap, int);
		p->cur_flags->prec = t < 0 ? -1 : t;
		*format = temp;
	}
	else
		p->cur_flags->prec = 0;
}

int		read_size(char **format, t_info *p)
{
	if (**format == 'l' && *(*format + 1) == 'l')
	{
		(*format)++;
		p->cur_flags->ll = 1;
	}
	else if (**format == 'h' && *(*format + 1) == 'h')
	{
		(*format)++;
		p->cur_flags->hh = 1;
	}
	else if (**format == 'z' || **format == 't')
		p->cur_flags->z = 1;
	else if (**format == 'l')
		p->cur_flags->l = 1;
	else if (**format == 'h')
		p->cur_flags->h = 1;
	else if (**format == 'j')
		p->cur_flags->j = 1;
	else if (**format == 'L')
		p->cur_flags->high_l = 1;
	else
		return (0);
	return (1);
}
