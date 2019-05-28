/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syeresko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 11:29:31 by syeresko          #+#    #+#             */
/*   Updated: 2019/05/28 17:33:18 by syeresko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
**	The following functions are an alternative way of using LIBFT's `t_list`.
**	They make no use of the `content_size` field.
**
**	`list_push` prepends a new item containing the specified content.
**	`list_pop` deletes the first item.		// TODO: and returns its content (?)
**
**	The trick to insert or remove an item in the middle or end of a list,
**	say right after an item pointd to by `t_list *item`, is to pass
**	`&item->next` as the `head` parameter to these functions.
*/

void		list_push(t_list **head, void *content)
{
	t_list	*item;

	if ((item = malloc(sizeof(t_list))) == NULL)
	{
		perror("list_push");
		exit(-1);
	}
	item->content = content;
	item->next = *head;
	*head = item;
}

void		list_pop(t_list **head)
{
	t_list	*item;

	item = *head;
	*head = item->next;
	free(item);
}

void		list_push_back(t_list **head, void *content)
{
	while (*head != NULL)
	{
		head = &(*head)->next;
	}
	list_push(head, content);
}
