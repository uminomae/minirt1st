/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:54:11 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:45:31 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALLOC_H
# define ALLOC_H

# include "common.h"

//----------------
// for malloc list
//----------------
typedef struct s_ptr_node
{
	void				*ptr;
	struct s_ptr_node	*next;
}t_ptr_node;

typedef struct s_ptr_list
{
	struct s_ptr_node	*head;
	struct s_ptr_node	*tail;
}t_ptr_list;

void	*minirt_malloc(t_ptr_list *ptr_list, size_t size);
bool	free_alloc_list_node(t_ptr_list *alloc_list);

#endif
