/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parallel_raytracer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:03:42 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:19:24 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// -----------------------------------
// raytracing_in_parallel
// -----------------------------------
static void	put_pixel_with_parallel(\
t_mlx *mlx, t_scene *scene, double x, double y)
{
	int			put_color;
	t_fcolor	material_c;
	t_fcolor	c;

	if (scene->nearest_t > 0)
	{
		material_c = scene->near_shape->material.material_color;
		c = multiply_fcolor(material_c, scene->radiance_all);
		put_color = build_trgb(1, (int)c.red, (int)c.green, (int)c.blue);
	}
	else
		put_color = scene->background_color;
	pthread_mutex_lock(scene->mutex);
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, put_color);
	pthread_mutex_unlock(scene->mutex);
}

void	*raytracing_in_parallel(void *ptr)
{
	double	x;
	double	y;
	t_para	*para;

	para = (t_para *)ptr;
	y = para->y_start;
	while (y < para->y_end)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			para->scene->nearest_t = raytracing_each_pixel(para->scene, x, y);
			put_pixel_with_parallel(para->scene->mlx, para->scene, x, y);
			x++;
		}
		y++;
	}
	return (ptr);
}
