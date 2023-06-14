/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_shadow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:17:19 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:24:22 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define EPSILON 512;

static void	init_shadow(t_shadow *shdw)
{
	ft_memset(shdw, 0, sizeof(t_shadow));
	shdw->epsilon = 1.0f / EPSILON;
}

// 影（交点）の位置から光源の方向を求める
// light position = 光源の位置ベクトルx,y,z
// pi = 交点の位置ベクトル = 影を判定する位置 hit_pos
// l_dir = distance_to_light //影の位置から光源までのベクトル
// d = shadow_ray.direction = 交点piから光源の方向
static t_vec3	build_direction_shadow_ray(\
t_scene *scene, t_shadow *shdw, t_light *light)
{
	const t_vec3	*pi = &scene->near_shape->hit_pos;

	shdw->l_dir = subtract_vec3(light->position, *pi);
	shdw->d = normalize_vec3(shdw->l_dir);
	return (shdw->d);
}

// 影（交点）の位置をd方向に微小距離移動する
// epsilon = 補正係数 //nearest判定に含まれないよう、わずかにずらす補正係数
// el = shadow_ray.direction + epsilon //視点を光源側にずらす距離
// shadow_ray_start_pos = 𝐩i→+𝜖ℓ⃗ // 補正後の影の位置x, y, z
static t_vec3	move_start_pos_epsiron(t_shadow *shdw, const t_vec3 *pi)
{
	t_vec3	shadow_ray_start_pos;

	shdw->el = multiply_vec3(shdw->d, shdw->epsilon);
	shadow_ray_start_pos = add_vec3(*pi, shdw->el);
	return (shadow_ray_start_pos);
}

// 落影の位置から光源までの間に物体があるかどうかを判定する
// dl = 𝐷ℓ = ∣∣𝐩ℓ→ – 𝐩i→∣∣ − 𝜖 = 交点piと点光源plの距離
// t = 交差判定で求める係数 = sから直近の物体との交差s + tdに用いる
static bool	is_near_than_light(t_shadow *shdw, double t)
{
	const t_vec3	d_t_mult = multiply_vec3(shdw->d, t);
	const double	d_t_norm = calculate_norm_vec3(d_t_mult);
	const double	dl = \
		calculate_norm_vec3(shdw->l_dir) - calculate_norm_vec3(shdw->el);

	if (t > 0 && d_t_norm < dl)
		return (true);
	return (false);
}

// scene->shadow_ray.start_pos = 始点の位置ベクトル
// scene->shadow_ray.direction = 始点から光源への方向
bool	is_shadow(t_scene *scene, t_light *light)
{
	t_shadow		shdw;
	double			t;
	const t_vec3	*p = &scene->near_shape->hit_pos;

	init_shadow(&shdw);
	scene->shadow_ray.direction = \
			build_direction_shadow_ray(scene, &shdw, light);
	scene->shadow_ray.start_pos = move_start_pos_epsiron(&shdw, p);
	t = hit_nearest(scene, true);
	if (t <= 0)
		return (false);
	return (is_near_than_light(&shdw, t));
}
