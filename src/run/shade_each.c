/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_each.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:52:35 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:39:04 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_radiance(t_radiance *rad)
{
	ft_memset(rad, 0, sizeof(t_radiance));
	rad->incident_angle = 0;
}

// 光源の方向ベクトルを求める
// light->position = 光源の位置
// pi = 𝐩i→ = 交点位置 = hit_pos
// l = pl - pi = 光源位置 - 交点位置
static t_vec3	build_incident_vector(t_scene *scene, t_light *light)
{
	const t_vec3	pi = scene->near_shape->hit_pos;
	const t_vec3	l = subtract_vec3(light->position, pi);

	return (normalize_vec3(l));
}

// 法線ベクトルと入射ベクトルの内積を求める
// ※内積の値を0~1の範囲に切り詰める。マイナスはゼロとして扱う
// normal = 法線ベクトル
// incident_angle = normal・l_dir = 入射角
static double	build_incident_angle(t_scene *scene, t_radiance *rad)
{
	const t_vec3	normal = scene->near_shape->hit_pos_normal;
	double			incident_angle;

	incident_angle = calculate_scalar_product(normal, rad->l_dir);
	if (incident_angle < 0)
		incident_angle = 0;
	return (incident_angle);
}

// 反射光の放射輝度を求める
// pi = 𝐩i→ = s + td = 交点位置 = nearest hit_pos
// l_dir = 入射ベクトル　= 光源の方向ベクトル（norm = 1）
// incident_angle = normal・l_dir = 法線ベクトルと入射ベクトルの内積
void	calculate_shade_each(\
t_scene *scene, double nearest_t, t_light *light)
{
	t_radiance	rad;
	t_fcolor	radiance_each;

	if (nearest_t > 0)
	{
		init_radiance(&rad);
		rad.l_dir = build_incident_vector(scene, light);
		rad.incident_angle = build_incident_angle(scene, &rad);
		radiance_each = build_radiance_each_light(scene, &rad, light);
		scene->radiance_all = \
			add_fcolor(scene->radiance_all, radiance_each);
	}
}
