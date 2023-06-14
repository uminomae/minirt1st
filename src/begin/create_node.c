/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:08:59 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 08:20:36 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//---------------------------------------------------------
// t_light:
//---------------------------------------------------------

t_light	*create_light(\
t_ptr_list *alloc_list, t_vec3 pos, double ratio, t_fcolor color)
{
	t_light		*light;
	t_fcolor	tmp_color;

	light = (t_light *)minirt_malloc(alloc_list, sizeof(t_light));
	light->type = LT_POINT;
	light->position = pos;
	light->brightness_ratio = ratio;
	light->color = color;
	tmp_color = multiply_fcolor_double(color, 1.0f / 255.0f);
	light->light_intensity = multiply_fcolor_double(tmp_color, ratio);
	light->next = NULL;
	return (light);
}

//---------------------------------------------------------
// t_shape:　create u_obj
//---------------------------------------------------------

static void	init_material(t_material *material)
{
	material->ambient_ref = build_fcolor(AMBIENT_R, AMBIENT_R, AMBIENT_R);
	material->diffuse_ref = build_fcolor(DIFFUSE_R, DIFFUSE_R, DIFFUSE_R);
	material->specular_ref = build_fcolor(SPECULAR_R, SPECULAR_R, SPECULAR_R);
	material->shininess = SHININESS;
}

t_shape	*create_sphere(t_vec3 center, double r, t_ptr_list *alloc_list)
{
	t_shape	*ret;

	ret = minirt_malloc(alloc_list, sizeof(t_shape));
	ret->type = ST_SPHERE;
	ret->u_obj.sphere.center = center;
	ret->u_obj.sphere.radius = r;
	init_material(&ret->material);
	ret->next = NULL;
	ret->t = -1;
	ret->hit_pos = build_vec3(-1, -1, -1);
	ret->hit_pos_normal = build_vec3(-1, -1, -1);
	return (ret);
}

t_shape	*create_plane(t_vec3 normal, t_vec3 position, t_ptr_list *alloc_list)
{
	t_shape	*ret;

	ret = minirt_malloc(alloc_list, sizeof(t_shape));
	ret->type = ST_PLANE;
	ret->u_obj.plane.normal = normal;
	ret->u_obj.plane.position = position;
	init_material(&ret->material);
	ret->next = NULL;
	ret->t = -1;
	ret->hit_pos = build_vec3(-1, -1, -1);
	ret->hit_pos_normal = build_vec3(-1, -1, -1);
	return (ret);
}

t_shape	*create_cylinder(\
t_vec3 center, double r, double height, t_ptr_list *alloc_list)
{
	t_shape	*ret;

	ret = minirt_malloc(alloc_list, sizeof(t_shape));
	ret->type = ST_CYLINDER;
	ret->u_obj.cylinder.center_pos = center;
	ret->u_obj.cylinder.radius = r;
	ret->u_obj.cylinder.height = height;
	init_material(&ret->material);
	ret->material.shininess = CY_SHININESS;
	ret->material.specular_ref = \
		build_fcolor(CY_SPECULAR_R, CY_SPECULAR_R, CY_SPECULAR_R);
	ret->next = NULL;
	ret->t = -1;
	ret->hit_pos = build_vec3(-1, -1, -1);
	ret->hit_pos_normal = build_vec3(-1, -1, -1);
	ret->u_obj.cylinder.disk.radius = r;
	ret->u_obj.cylinder.disk.position = \
			build_vec3(center.x, center.y + (height / 2), center.z);
	ret->u_obj.cylinder.disk_bottom.position = \
			build_vec3(center.x, center.y - (height / 2), center.z);
	ret->u_obj.cylinder.disk.normal = build_vec3(0, 1, 0);
	return (ret);
}
