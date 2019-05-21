/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaiko <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:07:39 by omaiko            #+#    #+#             */
/*   Updated: 2017/11/14 16:39:42 by omaiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_numberofwords(const char *s, char c)
{
	int			count;
	int			i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static int		ft_symbols(const char *s, char c, int start)
{
	int			i;

	i = start;
	while (s[i] && s[i] != c)
		i++;
	return (i - start);
}

static char		*ft_create_line(const char *s, char c, char *str, int start)
{
	int			i;

	i = 0;
	while (s[start] && s[start] != c)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}

static char		**ft_create_array(const char *s, char c, char **arrline)
{
	int			i;
	int			start;

	i = 0;
	start = 0;
	while (s[start])
	{
		while (s[start] && s[start] == c)
			start++;
		if (s[start] && s[start] != c)
		{
			if (!(arrline[i] = (char*)malloc(ft_symbols(s, c, start) + 1)))
				return (0);
			arrline[i] = ft_create_line(s, c, arrline[i], start);
			while (s[start] && s[start] != c)
				start++;
			i++;
		}
	}
	arrline[i] = 0;
	return (arrline);
}

char			**ft_strsplit(char const *s, char c)
{
	char		**arrline;
	int			i;

	i = 0;
	if (!s || !c)
		return (0);
	if (!(arrline = (char**)malloc(sizeof(char*) * ft_numberofwords(s, c) + 1)))
		return (0);
	arrline = ft_create_array(s, c, arrline);
	i = 0;
	while (i < ft_numberofwords(s, c))
	{
		if (!arrline[i])
			free(arrline[i]);
		i++;
	}
	return (arrline);
}
