/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vlvereta <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:29:49 by vlvereta          #+#    #+#             */
/*   Updated: 2017/10/29 18:29:44 by vlvereta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*tmp;

	if (lst && f)
	{
		tmp = lst;
		new = ft_lstnew(tmp->content, tmp->content_size);
		if (new)
		{
			new = f(new);
			if (tmp->next)
				new->next = ft_lstmap(tmp->next, f);
			return (new);
		}
	}
	return (NULL);
}
