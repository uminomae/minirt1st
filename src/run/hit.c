/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:06:07 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 12:07:51 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	detect_hit(\
t_scene *scene, t_shape *shape_node, bool flag_shadow)
{
	double	t;

	t = -1;
	if (shape_node->type == ST_SPHERE)
		t = detect_hit_of_sphere(scene, shape_node, flag_shadow);
	else if (shape_node->type == ST_PLANE)
		t = detect_hit_of_plane(scene, shape_node, flag_shadow);
	else if (shape_node->type == ST_CYLINDER)
		t = detect_hit_of_cylinder(scene, shape_node, flag_shadow);
	return (t);
}

//始点(カメラor落影)から交点までの間に物体があるかどうかを判定する
double	hit_nearest(t_scene *scene, bool flag_shadow)
{
	double	nearest_t;
	bool	hit;
	double	t;
	t_shape	*shape_node;

	nearest_t = __DBL_MAX__;
	hit = false;
	shape_node = scene->shape_list.head;
	while (shape_node != NULL)
	{
		t = detect_hit(scene, shape_node, flag_shadow);
		if (t > 0 && t < nearest_t)
		{
			hit = true;
			if (flag_shadow == false)
				scene->near_shape = shape_node;
			nearest_t = t;
		}
		shape_node = shape_node->next;
	}
	if (hit == false)
		nearest_t = -1;
	return (nearest_t);
}
