/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_free_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/06 15:11:49 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:45:31 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	free_alloc_list_ptr(t_ptr_list *alloc_list)
{
	t_ptr_node	*node;

	if (alloc_list == NULL)
		return (false);
	if (alloc_list->head == NULL)
		return (false);
	node = alloc_list->head;
	while (node != NULL)
	{
		free(node->ptr);
		node->ptr = NULL;
		node = node->next;
	}
	return (true);
}

bool	free_alloc_list_node(t_ptr_list *alloc_list)
{
	t_ptr_node	*node;
	t_ptr_node	*tmp;

	if (alloc_list == NULL)
		return (false);
	if (alloc_list->head == NULL)
		return (false);
	node = alloc_list->head;
	while (node != NULL)
	{
		tmp = node;
		node = node->next;
		free(tmp);
		tmp = NULL;
	}
	return (true);
}

bool	free_alloc_list(t_ptr_list *alloc_list)
{
	if (free_alloc_list_ptr(alloc_list) == false)
		return (false);
	if (free_alloc_list_node(alloc_list) == false)
		return (false);
	return (true);
}
