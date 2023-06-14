/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_sphere.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:47:27 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 22:52:46 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//-----------------------------
// Sphere intersection detection
//-----------------------------

// scene->ray.s_pos = 𝐩𝐞−→ = カメラの位置
// scene->ray.direction = カメラからスクリーン画素への方向ベクトル（norm = 1）
// scene->shadow_ray.s_pos = 物体とカメラの交点 
// scene->shadow_ray.direction = 物体から光源への方向ベクトル（norm = 1）
void	init_sp(t_scene *scene, t_detect_sp *sp, bool flag_shadow)
{
	ft_memset(sp, 0, sizeof(t_detect_sp));
	sp->ray = scene->ray;
	if (flag_shadow == true)
		sp->ray = scene->shadow_ray;
}

void	build_ray_sphere(t_detect_sp *sp, const t_vec3 *obj_pos)
{
	sp->dir = sp->ray.direction;
	sp->s = subtract_vec3(sp->ray.start_pos, *obj_pos);
}

// s_pos = 開始点(カメラ)の位置ベクトル
// obj_position = 中心位置ベクトル
// s = 中心から開始点位置へのベクトル = m
// dir = |𝐝⃗|
static double	get_nearest_t(double a, double b, double d)
{
	double	t;
	double	t1;
	double	t2;

	t = -1;
	if (d == 0)
		t = -b / (2 * a);
	else if (d > 0)
	{
		t1 = (-b + sqrt(d)) / (2 * a);
		t2 = (-b - sqrt(d)) / (2 * a);
		if (0 < t1)
			t = t1;
		if (0 < t2 && t2 < t1)
			t = t2;
	}
	return (t);
}

//sphere
// a = |𝐝⃗|の2乗
// b = 2(𝐬⃗⋅𝐝⃗)
// c = |𝐬⃗|の2乗 − 𝑟の2乗
// d = 𝐵の2乗−4𝐴𝐶
//cylinder
// a = A =|𝐝⃗𝐌|の2乗
// b = B = 2(𝐬⃗𝐌⋅𝐝⃗𝐌) //𝐬⃗ = 𝐦⃗ 
// c = C =|𝐬⃗|の2乗 − 𝑟の2乗 //𝐬⃗ = 𝐦⃗
double	build_t_sphere(t_vec3 s, t_vec3 dir, double r)
{
	double	t;
	double	a;
	double	b;
	double	c;
	double	d;

	a = pow(calculate_norm_vec3(dir), 2);
	b = 2 * calculate_scalar_product(s, dir);
	c = calculate_scalar_product(s, s) - pow(r, 2);
	d = pow(b, 2) - 4 * a * c;
	t = get_nearest_t(a, b, d);
	return (t);
}

// s_pos = 開始点(カメラ)の位置ベクトル
// obj_position = 中心位置ベクトル
// s = 中心から開始点位置へのベクトル = m
// dir = |𝐝⃗|
double	detect_hit_of_sphere(t_scene *scene, t_shape *shape, bool flag_shadow)
{
	const t_vec3	*obj_pos = &shape->u_obj.sphere.center;
	const double	radius = shape->u_obj.sphere.radius;
	t_detect_sp		sp;
	double			t;

	init_sp(scene, &sp, flag_shadow);
	build_ray_sphere(&sp, obj_pos);
	t = build_t_sphere(sp.s, sp.dir, radius);
	if (flag_shadow == false)
		build_hit_info(scene, shape, t);
	return (t);
}
