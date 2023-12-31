/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 00:43:12 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:12:29 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	make_first_ptr_node(t_ptr_list *list, t_ptr_node *node)
{
	list->head = node;
	list->tail = node;
}

static void	add_last_ptr_node(t_ptr_list *list, t_ptr_node *node)
{
	list->tail->next = node;
	list->tail = node;
}

static t_ptr_node	*init_ptr_node(void)
{
	t_ptr_node	*node;

	node = (t_ptr_node *)malloc(sizeof(t_ptr_node));
	if (node == NULL)
		return (NULL);
	ft_memset(node, 0, sizeof(t_ptr_node));
	return (node);
}

static void	*add_ptr_list(t_ptr_list *ptr_list, void *ptr)
{
	t_ptr_node	*node;

	node = init_ptr_node();
	if (node == NULL)
		return (NULL);
	node->ptr = ptr;
	if (ptr_list->head == NULL)
		make_first_ptr_node(ptr_list, node);
	else
		add_last_ptr_node(ptr_list, node);
	return (node);
}

void	*minirt_malloc(t_ptr_list *ptr_list, size_t size)
{
	void	*ptr;
	void	*ret;

	ptr = malloc(size);
	if (ptr == NULL)
		return (NULL);
	ft_memset(ptr, 0, size);
	ret = add_ptr_list(ptr_list, ptr);
	if (ret == NULL)
		return (NULL);
	return (ptr);
}
