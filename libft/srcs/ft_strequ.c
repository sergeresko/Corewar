/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 15:51:26 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 15:54:34 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strequ(char const *s1, char const *s2)
{
	unsigned int i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] || s2[i])
		{
			if (((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
				return (0);
			i++;
		}
	}
	else
		return (0);
	return (1);
}
