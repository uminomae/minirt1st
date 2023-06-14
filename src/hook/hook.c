/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:50:33 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 21:55:17 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_window(t_scene *scene)
{
	t_mlx	*mlx;

	mlx = scene->mlx;
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(0);
}

void	hook_mlx(\
t_mlx *mlx, t_scene *scene, t_ptr_list *alloc_list, t_para *para)
{
	memset(para, 0, sizeof(t_para));
	scene->alloc_list = alloc_list;
	scene->mlx = mlx;
	para->scene = scene;
	mlx_key_hook(mlx->win_ptr, &operate_with_key, para);
	mlx_mouse_hook(mlx->win_ptr, &operate_with_mouse, para);
	mlx_hook(mlx->win_ptr, ON_DESTROY, 0, &close_window, scene);
}
