/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_high_c.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/22 12:34:58 by vlvereta          #+#    #+#             */
/*   Updated: 2018/01/22 12:35:08 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		type_high_c(void *info)
{
	wchar_t	c;
	t_info	*p;
	int		len;
	char	*unichar;

	p = (t_info *)info;
	if ((c = va_arg(p->ap, wchar_t)) < 128)
		char_to_output(p, c);
	else if ((unichar = ft_strnew(4)))
	{
		if (!(len = wchar_encoder(c, &unichar)))
		{
			char_to_output(p, c);
			return (clean_return(unichar, 0, 0, -1));
		}
		if (p->cur_flags->width > len)
			width_for_unichar(p, unichar, len);
		else
			string_to_output(p, unichar, len);
	}
	return (1);
}

int		wchar_encoder(unsigned int c, char **unichar)
{
	if (c < 2048)
	{
		**unichar = c >> 6 | 0xC0;
		*(*unichar + 1) = (c << 26) >> 26 | 0x80;
		return (MB_CUR_MAX < 2 ? 0 : 2);
	}
	else if (c < 65536)
	{
		**unichar = ((c >> 12) << 28) >> 28 | 0xE0;
		*(*unichar + 1) = ((c >> 6) << 26) >> 26 | 0x80;
		*(*unichar + 2) = (c << 26) >> 26 | 0x80;
		return (MB_CUR_MAX < 3 ? 0 : 3);
	}
	else
	{
		**unichar = ((c >> 18) << 29) >> 29 | 0xF0;
		*(*unichar + 1) = ((c >> 12) << 26) >> 26 | 0x80;
		*(*unichar + 2) = ((c >> 6) << 26) >> 26 | 0x80;
		*(*unichar + 3) = (c << 26) >> 26 | 0x80;
		return (MB_CUR_MAX < 4 ? 0 : 4);
	}
}

void	width_for_unichar(t_info *p, char *unichar, int len)
{
	char	*temp;
	char	*result;

	if ((temp = ft_strnew(p->cur_flags->width - len)))
	{
		if (p->cur_flags->zero && !p->cur_flags->left)
			ft_memset(temp, '0', p->cur_flags->width - len);
		else
			ft_memset(temp, ' ', p->cur_flags->width - len);
		result = p->cur_flags->left ? ft_strjoin(unichar, temp)
			: ft_strjoin(temp, unichar);
		string_to_output(p, result, p->cur_flags->width);
		free(temp);
		free(unichar);
	}
}
