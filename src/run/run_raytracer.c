/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_raytracer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:10:09 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 16:04:11 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	run_raytracer(t_mlx *mlx, t_scene *scene)
{
	double	x;
	double	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			scene->nearest_t = raytracing_each_pixel(scene, x, y);
			put_each_pixel(mlx, scene, x, y);
			x++;
		}
		y++;
	}
	return (0);
}

double	raytracing_each_pixel(t_scene *scene, double x, double y)
{
	double	nearest_t;

	nearest_t = -1;
	build_camera_screen(scene, x, y);
	nearest_t = hit_nearest(scene, false);
	if (nearest_t <= 0)
		return (-1);
	calculate_shade(scene, nearest_t);
	return (nearest_t);
}

void	put_each_pixel(t_mlx *mlx, t_scene *scene, double x, double y)
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
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, put_color);
}
