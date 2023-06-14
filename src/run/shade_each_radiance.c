/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade_radiance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:52:02 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 08:05:46 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//---------------------------------------------------------
// shade Phong model
//---------------------------------------------------------

// kd = 𝑘𝑑 = diffuse reflection coefficient = 拡散反射係数
// ii = 𝐼𝑖 = light_intensity = 光源の光の強度
// rd = 𝑅𝑑 = 𝑘𝑑𝐼𝑖(𝐧⃗ ⋅ℓ⃗ ) = 直接光の拡散反射光の放射輝度
static t_fcolor	build_diffuse_light_radiance(\
t_scene *scene, t_light *light, double incident_angle)
{
	t_fcolor	kd;
	t_fcolor	ii;
	t_fcolor	kd_ii;
	t_fcolor	rd;

	if (incident_angle < 0)
		return (build_fcolor(0, 0, 0));
	kd = scene->near_shape->material.diffuse_ref;
	ii = light->light_intensity;
	kd_ii = multiply_fcolor(kd, ii);
	rd = multiply_fcolor_double(kd_ii, incident_angle);
	return (rd);
}

// ray_dir = 視線の方向
// hit_pos_normal = 反射面の法線
// 𝐯⃗ = −𝐝e→ = 視線ベクトルの逆ベクトル //d = 視線dir
// 𝐫⃗ = 2(𝐧⃗ ⋅ℓ⃗ )𝐧⃗ −ℓ⃗  = 入射光の正反射ベクトル
// vr = (𝐯⃗ ⋅𝐫⃗ ) = 内積(𝐯⃗ ⋅𝐫⃗ ) //vとrの角度の差  //※負の場合0　
double	build_difference_specular_ref_angle_and_camera_dir(\
t_radiance *rad, t_vec3 ray_dir, t_vec3 hit_pos_normal)
{
	const t_vec3	v = multiply_vec3(ray_dir, REVERSE_DIRECTION);
	const t_vec3	reflection_vec_of_light = \
						multiply_vec3(hit_pos_normal, 2 * rad->incident_angle);
	const t_vec3	r = subtract_vec3(reflection_vec_of_light, rad->l_dir);
	double			vr;

	vr = calculate_scalar_product(v, r);
	if (vr < 0)
		vr = 0;
	return (vr);
}

// dir = 視線の方向
// normal = 反射面の法線
// vr = (𝐯⃗ ⋅𝐫⃗ ) = 内積(𝐯⃗ ⋅𝐫⃗ )
// vr_pow_a = 内積(𝐯⃗ ⋅𝐫⃗ )のa乗
// shininess = 𝛼 = 光沢度;
// light_intensity = 光源の光の強度
// specular_ref = 𝑘𝑠 = 鏡面反射係数
// return = 𝑘𝑠𝐼𝑖(𝐯⃗ ⋅𝐫⃗ )𝛼 = 直接光の鏡面反射光の放射輝度
static t_fcolor	build_specular_glow_radiance(\
t_scene *scene, t_radiance *rad, t_light *light, const t_material *material)
{
	const t_vec3	ray_dir = scene->ray.direction;
	const t_vec3	hito_pos_normal = scene->near_shape->hit_pos_normal;
	const double	vr = \
				build_difference_specular_ref_angle_and_camera_dir(\
				rad, ray_dir, hito_pos_normal);
	const double	vr_pow_a = pow(vr, material->shininess);
	const t_fcolor	ii_pow = \
		multiply_fcolor_double(light->light_intensity, vr_pow_a);

	return (multiply_fcolor(material->specular_ref, ii_pow));
}

// rd = 𝑅𝑑 = 𝑘𝑑𝐼𝑖(𝐧⃗ ⋅ℓ⃗ ) = 直接光の拡散反射光の放射輝度
// rs = 𝑅𝑠 = 𝑘𝑠𝐼𝑖(𝐯⃗ ⋅𝐫⃗ )𝛼 = 直接光の鏡面反射光の放射輝度
t_fcolor	build_radiance_each_light(\
t_scene *scene, t_radiance *rad, t_light *light)
{
	const t_material	*material = &scene->near_shape->material;
	const t_fcolor		rd = \
			build_diffuse_light_radiance(scene, light, rad->incident_angle);
	const t_fcolor		rs = \
			build_specular_glow_radiance(scene, rad, light, material);

	if (scene->near_shape->no_light == true)
		return (build_fcolor(0, 0, 0));
	return (add_fcolor(rd, rs));
}
