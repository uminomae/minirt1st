/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:50:33 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 09:27:53 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	move_camera(double *start_pos_coordinate, double coordinate_value)
{
	*start_pos_coordinate += coordinate_value;
}

void	rotate_camera(t_para *para, double degree, double x, double y)
{
	const t_vec3	axis = build_vec3(x, y, 0);
	const double	radian = -1 * degree * M_PI / 180;

	para->scene->ray.look_at = \
		rotate_angle_axis(axis, radian, false, para->scene->ray.look_at);
	para->scene->ray.view_up = \
		rotate_angle_axis(axis, radian, false, para->scene->ray.view_up);
}

void	zoom_camera(double *fov, double degree, bool *run)
{
	const double	tmp = *fov;

	*fov += degree;
	if (*fov < 0 || 180 < *fov)
	{
		*fov = tmp;
		*run = false;
		return ;
	}
	*run = true;
	return ;
}

bool	move_light(t_light *light, int add_x, int add_y, int add_z)
{
	light->position.x += add_x;
	light->position.y += add_y;
	light->position.z += add_z;
	if (light->position.y < 0.1)
	{
		light->position.y = 1;
		return (false);
	}
	return (true);
}
