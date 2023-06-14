/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:50:33 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 22:24:33 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	case_z_nega(t_para *para)
{
	double	tmp;

	tmp = para->shape_mouse->u_obj.sphere.center.z;
	para->shape_mouse->u_obj.sphere.center.z -= 0.5;
	if (para->shape_mouse->u_obj.sphere.center.z <= \
		para->shape_mouse->u_obj.sphere.radius)
	{
		para->shape_mouse->u_obj.sphere.center.z = tmp;
		return (false);
	}
	return (true);
}

void	operate_with_num_keys_sp(t_para *para, int keycode)
{
	if (para->shape_mouse == NULL || para->shape_mouse->type != ST_SPHERE)
		return ;
	if (keycode == MAC_OS_KEY_1)
		para->shape_mouse->u_obj.sphere.center.x -= 0.5;
	else if (keycode == MAC_OS_KEY_7)
		para->shape_mouse->u_obj.sphere.center.x += 0.5;
	else if (keycode == MAC_OS_KEY_2)
		para->shape_mouse->u_obj.sphere.center.y -= 0.5;
	else if (keycode == MAC_OS_KEY_8)
		para->shape_mouse->u_obj.sphere.center.y += 0.5;
	else if (keycode == MAC_OS_KEY_3)
	{
		if (case_z_nega(para) == false)
			return ;
	}
	else if (keycode == MAC_OS_KEY_9)
		para->shape_mouse->u_obj.sphere.center.z += 0.5;
	else
		return ;
	put_vec_rt_format(para->shape_mouse->u_obj.sphere.center, "sp");
	run_parallel(para);
}

void	operate_with_num_keys_cy(t_para *para, int keycode)
{
	const t_vec3	axis = build_vec3(1, 0, 0);
	const double	angle = 60 * M_PI / 180;
	t_vec3			*cy_axis;

	if (para->shape_mouse == NULL)
		return ;
	if (para->shape_mouse->type != ST_CYLINDER)
		return ;
	cy_axis = &para->shape_mouse->u_obj.cylinder.axis;
	if (keycode == MAC_OS_KEY_4)
		*cy_axis = rotate_angle_axis(axis, angle, false, *cy_axis);
	else if (keycode == MAC_OS_KEY_5)
		*cy_axis = rotate_angle_axis(axis, -1 * angle, false, *cy_axis);
	else
		return ;
	put_vec_rt_format(para->shape_mouse->u_obj.cylinder.axis, "cy");
	run_parallel(para);
}

void	operate_with_num_keys_material(t_para *para, int keycode)
{
	t_fcolor		*m_color;

	if (para->shape_mouse == NULL)
		return ;
	if (para->shape_mouse->type != ST_SPHERE && \
		para->shape_mouse->type != ST_CYLINDER)
		return ;
	m_color = &para->shape_mouse->material.material_color;
	if (keycode == MAC_OS_KEY_A)
		m_color->red = (int)(m_color->red + 30.0) % 256;
	else if (keycode == MAC_OS_KEY_G)
		m_color->green = (int)(m_color->green + 30.0) % 256;
	else if (keycode == MAC_OS_KEY_B)
		m_color->blue = (int)(m_color->blue + 30.0) % 256;
	else
		return ;
	put_rgb_rt_format(para->shape_mouse->material.material_color);
	run_parallel(para);
}
