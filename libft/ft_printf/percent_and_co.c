/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   percent_and_co.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 23:15:03 by vlvereta          #+#    #+#             */
/*   Updated: 2018/02/01 23:18:32 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		percent_handling(void *info)
{
	char	c;
	t_info	*p;

	c = '%';
	p = (t_info *)info;
	char_to_output(p, c);
	return (1);
}

int		type_low_c(void *info)
{
	char	c;
	t_info	*p;

	p = (t_info *)info;
	if (p->cur_flags->l)
		return (type_high_c(p));
	c = (char)va_arg(p->ap, int);
	char_to_output(p, c);
	return (1);
}

void	char_to_output(t_info *p, char c)
{
	int		i;
	char	*temp;

	if (p->cur_flags->width > 1)
		width_for_char(p, c);
	else if ((temp = ft_strnew(++p->outlen)))
	{
		i = 0;
		while (i < p->outlen - 1)
		{
			temp[i] = p->output[i];
			i++;
		}
		temp[i] = c;
		free(p->output);
		p->output = temp;
	}
}

void	width_for_char(t_info *p, char c)
{
	int		i;
	char	*result;

	if ((result = ft_strnew(p->cur_flags->width)))
	{
		if (p->cur_flags->zero && !p->cur_flags->left)
			ft_memset(result, '0', p->cur_flags->width);
		else
			ft_memset(result, ' ', p->cur_flags->width);
		i = p->cur_flags->left && c ? 0 : p->cur_flags->width - 1;
		result[i] = c;
		string_to_output(p, result, p->cur_flags->width);
	}
}

void	string_to_output(t_info *p, char *s, int len)
{
	int		i;
	int		j;
	int		new_len;
	char	*result;

	if (s && *s)
	{
		new_len = p->outlen + len;
		if ((result = ft_strnew(new_len)))
		{
			i = 0;
			j = 0;
			while (i < p->outlen)
				result[j++] = p->output[i++];
			free(p->output);
			i = 0;
			while (i < len)
				result[j++] = s[i++];
			free(s);
			p->output = result;
			p->outlen = new_len;
		}
	}
}
