/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:06:07 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 16:21:00 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 中心位置𝐩c→=(𝑐𝑥,𝑐𝑦,𝑐𝑧)
// (𝑥−𝑐𝑥)2+(𝑧−𝑐𝑧)2=𝑟2 = 円柱の方程式
// 交点𝐩a→=(𝑎𝑥,𝑎𝑦,𝑎𝑧)
// 法線ベクトル𝐧⃗ =(𝑛𝑥,𝑛𝑦,𝑛𝑧)
static t_vec3	build_hit_pos_normal(t_shape *shape)
{
	t_vec3	tmp_n;
	t_vec3	center;
	t_vec3	hit_pos_normal;

	hit_pos_normal = build_vec3(0, 0, 0);
	if (shape->type == ST_SPHERE)
	{
		center = shape->u_obj.sphere.center;
		tmp_n = subtract_vec3(shape->hit_pos, center);
		hit_pos_normal = normalize_vec3(tmp_n);
	}
	else if (shape->type == ST_PLANE)
	{
		hit_pos_normal = shape->u_obj.plane.normal;
	}
	return (hit_pos_normal);
}

// s_pos = 原点からカメラへの位置ベクトル　= scene->ray.start_pos
// hit_pos = 𝐬⃗ +𝑡𝐝⃗ 
// hit_pos_normal = 法線
t_vec3	build_hit_pos(t_scene *scene, double t)
{
	t_vec3	s_pos;
	t_vec3	d;
	t_vec3	td;
	t_vec3	hit_pos;

	s_pos = scene->ray.start_pos;
	d = scene->ray.direction;
	td = multiply_vec3(d, t);
	hit_pos = add_vec3(s_pos, td);
	return (hit_pos);
}

// 平面が光源とカメラの間にある場合、反射光をゼロにするフラグを立てる
static void	validate_between_camera_and_light_plane(\
t_scene *scene, t_shape *shape)
{
	const t_vec3	sub_s_p = \
			subtract_vec3(scene->ray.start_pos, shape->hit_pos);
	const t_vec3	n_sub = normalize_vec3(sub_s_p);
	const double	dot_sub_hitposnormal = \
			calculate_scalar_product(n_sub, shape->hit_pos_normal);

	if (dot_sub_hitposnormal < 0 && shape->type == ST_PLANE)
		shape->no_light = true;
}

static void	validate_between_camera_and_light_sphere(\
t_scene *scene, t_shape *shape)
{
	const t_vec3	cmpos = \
			subtract_vec3(shape->u_obj.sphere.center, scene->ray.start_pos);
	const double	norm_cmpos = calculate_norm_vec3(cmpos);

	if (shape->u_obj.sphere.radius > norm_cmpos && shape->type == ST_SPHERE)
		shape->no_light = true;
}

void	build_hit_info(t_scene *scene, t_shape *shape, double t)
{
	shape->hit_pos = build_hit_pos(scene, t);
	shape->hit_pos_normal = build_hit_pos_normal(shape);
	validate_between_camera_and_light_plane(scene, shape);
	validate_between_camera_and_light_sphere(scene, shape);
}
