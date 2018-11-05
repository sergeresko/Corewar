/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:34:58 by vlvereta          #+#    #+#             */
/*   Updated: 2018/01/22 12:35:08 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long long	to_unsigned(t_info *p)
{
	if (p->cur_flags->z)
		return (va_arg(p->ap, size_t));
	else if (p->cur_flags->j)
		return (va_arg(p->ap, uintmax_t));
	else if (p->cur_flags->ll)
		return (va_arg(p->ap, unsigned long long));
	else if (p->cur_flags->l)
		return (va_arg(p->ap, unsigned long));
	else if (p->cur_flags->h)
		return ((unsigned short)va_arg(p->ap, int));
	else if (p->cur_flags->hh)
		return ((unsigned char)va_arg(p->ap, int));
	else
		return (va_arg(p->ap, unsigned int));
}

char				*llu_base(unsigned long long value, int base)
{
	int					size;
	char				*result;
	unsigned long long	temp;

	temp = value;
	size = (!value ? 1 : 0);
	while (temp)
	{
		temp /= base;
		size++;
	}
	if ((result = (char *)malloc(sizeof(char) * (size + 1))))
	{
		result[size] = '\0';
		if (!value)
			result[--size] = '0';
		while (value)
		{
			temp = value % base;
			result[--size] = (temp > 9 ? temp + 87 : temp + '0');
			value /= base;
		}
	}
	return (result);
}

int					clean_return(void *ptr1, void *ptr2, void *ptr3, int ret)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	return (ret);
}
