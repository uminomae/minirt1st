/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:52:35 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:38:37 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_fcolor	build_ambient_light_radiance(t_scene *scene);
static void		radiance_to_upper_limit(t_scene *scene);

// pi = 𝐩i→ = s + td = 交点位置 = hit_nearest_pos
// l_dir = 入射ベクトル　= 光源の方向ベクトル（norm = 1）
// nl_dot = normal・l_dir = 法線ベクトルと入射ベクトルの内積
void	calculate_shade(t_scene *scene, double nearest_t)
{
	t_light	*light;

	if (scene->near_shape == NULL)
		return ;
	scene->radiance_all = build_ambient_light_radiance(scene);
	light = scene->light_list.head;
	while (light)
	{
		if (is_shadow(scene, light) == false)
			calculate_shade_each(scene, nearest_t, light);
		light = light->next;
	}
	radiance_to_upper_limit(scene);
}

//---------------------------------------------------------
// satic
//---------------------------------------------------------

// ia = 𝐼𝑎 = ambient_radiance = 環境光の強度
// mat_amb_ref = 物体の環境光の反射係数
// ka = 𝑘𝑎 = Ambient light reflection coefficient = 色補正後環境光反射係数
// ra = 𝑅𝑎 = 𝑘𝑎𝐼𝑎 = Radiance of reflected light of ambient light = 環境光の反射光の放射輝度
static t_fcolor	build_ambient_light_radiance(t_scene *scene)
{
	const t_fcolor	ia = scene->ambient_intensity;
	const t_fcolor	mat_amb_ref = scene->near_shape->material.ambient_ref;
	const t_fcolor	ka = multiply_fcolor_double(mat_amb_ref, 1.0f / 255.0f);
	const t_fcolor	ra = multiply_fcolor(ka, ia);

	return (ra);
}

static void	radiance_to_upper_limit(t_scene *scene)
{
	if (scene->radiance_all.red > 1)
		scene->radiance_all.red = 1;
	if (scene->radiance_all.green > 1)
		scene->radiance_all.green = 1;
	if (scene->radiance_all.blue > 1)
		scene->radiance_all.blue = 1;
}
