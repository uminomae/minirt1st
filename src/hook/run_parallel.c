/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_parallel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 12:35:23 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:49:05 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct s_run_para
{
	pthread_mutex_t		mutex;
	t_ptr_list			para_alloc_list;
	t_para				para[PARA_ARRAY];
	pthread_t			thread[PARA_ARRAY];
	t_scene				scene_cpy[PARA_ARRAY];
	t_ptr_list			alloc_list[PARA_ARRAY];
	t_shape_list		shape_list_cpy[PARA_ARRAY];
}t_run_para;

static void	copy_shape(t_shape_list *origin_list, \
t_shape_list *shape_list_cpy, t_ptr_list *rp_alloc_list)
{
	const t_shape	*origin_node = origin_list->head;
	t_shape			*new_shape;

	ft_memset(shape_list_cpy, 0, sizeof(t_shape_list));
	while (origin_node != NULL)
	{
		new_shape = minirt_malloc(rp_alloc_list, sizeof(t_shape));
		ft_memset(new_shape, 0, sizeof(t_shape *));
		*new_shape = *origin_node;
		add_list_shape(shape_list_cpy, new_shape);
		origin_node = origin_node->next;
	}
}

// 処理の流れ
// rp->para[i] = *para; //pthread用のt_para型の値のコピー
// rp->scene_cpy[i] = *para->scene; //scene_tの値をコピー
// rp->para[i].scene = &rp->scene_cpy[i]; //scene_t値を入れたメモリ領域のポインタをコピー
// rp->para[i].alloc_list = &rp->alloc_list[i]; //メモリ領域はスタックに確保
// copy_shape(origin_list, &rp->shape_list_cpy[i], &para[i]->alloc_list); 
//	リストに値をコピー
// rp->para[i].scene->shape_list_cpy = rp->shape_list_cpy[i]; //prara_t型に持たせる
// rp->para[i].y_start = i * 100; rp->para[i].y_end = i * 100 + 100; 
//	スレッドに分担させる行を指定　y=y_start; while(y < y_end){};
static void	run_pthread_create(\
t_run_para *rp, t_para *para, t_shape_list *origin_list)
{
	size_t			i;
	const size_t	add_y = WIN_HEIGHT % AMOUNT_OF_ROWS;

	i = 0;
	while (i < NUM_OF_THREADS)
	{
		rp->para[i] = *para;
		rp->scene_cpy[i] = *para->scene;
		rp->para[i].scene = &rp->scene_cpy[i];
		rp->para[i].scene->alloc_list = &rp->alloc_list[i];
		copy_shape(origin_list, \
			&rp->shape_list_cpy[i], rp->para[i].scene->alloc_list);
		rp->para[i].scene->shape_list = rp->shape_list_cpy[i];
		rp->para[i].y_start = i * AMOUNT_OF_ROWS;
		if (i == (size_t)NUM_OF_THREADS - 1)
			rp->para[i].y_end = i * AMOUNT_OF_ROWS + AMOUNT_OF_ROWS + add_y;
		else
			rp->para[i].y_end = i * AMOUNT_OF_ROWS + AMOUNT_OF_ROWS;
		pthread_create(\
			&rp->thread[i], NULL, raytracing_in_parallel, (void *)&rp->para[i]);
		i++;
	}
}

static void	run_pthread_join(t_run_para *rp)
{
	size_t	i;

	i = 0;
	while (i < NUM_OF_THREADS)
	{
		pthread_join(rp->thread[i], NULL);
		i++;
	}
}

static void	free_para_alloc_list_node(t_run_para *rp)
{
	size_t	i;

	i = 0;
	while (i < NUM_OF_THREADS)
	{
		free_alloc_list_node(rp->para[i].scene->alloc_list);
		i++;
	}
}

void	run_parallel(t_para *para)
{
	t_run_para	rp;

	ft_memset(&rp, 0, sizeof(t_run_para));
	pthread_mutex_init(&rp.mutex, NULL);
	para->scene->mutex = &rp.mutex;
	run_pthread_create(&rp, para, &para->scene->shape_list);
	run_pthread_join(&rp);
	pthread_mutex_destroy(&rp.mutex);
	free_para_alloc_list_node(&rp);
}
