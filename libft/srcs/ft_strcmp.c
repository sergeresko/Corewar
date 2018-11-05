/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 16:43:27 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/26 16:46:12 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned int	i;
	unsigned char	a;
	unsigned char	b;

	i = 0;
	while (s1[i] || s2[i])
	{
		a = ((unsigned char *)s1)[i];
		b = ((unsigned char *)s2)[i];
		if (a != b)
			return (a - b);
		i++;
	}
	return (0);
}
