/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_shape_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:43:12 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:11:06 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	make_first_ptr_node(t_shape_list *list, t_shape *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_ptr_node(t_shape_list *list, t_shape *node)
{
	list->tail->next = node;
	list->tail = node;
}

void	add_list_shape(t_shape_list *list, t_shape *node)
{
	if (list->head == NULL)
		make_first_ptr_node(list, node);
	else
		add_last_ptr_node(list, node);
}
