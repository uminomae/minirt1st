/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:49:49 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 19:19:31 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//回転軸rot_axisと角度rot_angleを求める　※外積の計算順序は左手系
// vwup = カメラの上方向 = world座標のy軸の正方向 = 0,1,0
// cyax = 円柱の軸（.rtで指定） = invalidなrt fileの値に対応。
// cross_cyax_vwup = 外積
// rot_axis = 任意の回転軸 = 左手系なのでcyaxから計算 
// rot_angle = 角度をcosθから求める = 内積cosθ ->ラジアンに変換
static void	build_angle_axis(t_scene *scene, t_shape *shape_node)
{
	const t_vec3	cyax = normalize_vec3(shape_node->u_obj.cylinder.axis);
	const t_vec3	cross_vwup_cyax = \
			calculate_vector_product(scene->y_axis, cyax);
	double			cos_theta;
	double			radian;

	shape_node->rot_axis = normalize_vec3(cross_vwup_cyax);
	cos_theta = calculate_scalar_product(scene->y_axis, cyax);
	radian = acos(cos_theta);
	shape_node->rot_angle = -1 * radian;
	(void)scene;
}

// 天井の法線を円柱軸と同じにする。
// bottomならば法線を円柱軸の逆方向にする
static double	build_hit_info_cy_disk(\
t_scene *scene, t_shape *shape_node, t_detect_pl *pl, bool flag_shadow)
{
	if (flag_shadow == false)
	{
		shape_node->hit_pos = build_hit_pos(scene, pl->t);
		if (pl->disk_bottom)
			shape_node->hit_pos_normal = \
				multiply_vec3(shape_node->u_obj.cylinder.axis, -1);
		else
			shape_node->hit_pos_normal = shape_node->u_obj.cylinder.axis;
	}
	return (pl->t);
}

static void	detect_hit_disk_top(t_shape *shape_node, t_detect_pl *pl)
{
	pl->obj_pos = shape_node->u_obj.cylinder.disk.position;
	pl->normal = build_vec3(0, 1, 0);
	pl->t = detect_hit_cylinder_disk(pl, shape_node);
	pl->disk_bottom = false;
}

static void	detect_hit_disk_bottom(t_shape *shape_node, t_detect_pl *pl)
{
	pl->obj_pos = shape_node->u_obj.cylinder.disk_bottom.position;
	pl->normal = build_vec3(0, -1, 0);
	pl->t = detect_hit_cylinder_disk(pl, shape_node);
	pl->disk_bottom = true;
}

double	detect_hit_of_cylinder(\
t_scene *scene, t_shape *shape_node, bool flag_shadow)
{
	t_detect_sp		sp;
	t_detect_pl		pl;
	double			t;

	t = 0;
	build_angle_axis(scene, shape_node);
	t = detect_hit_cylinder_side(scene, &sp, shape_node, flag_shadow);
	if (flag_shadow == false)
		build_hit_info_cy_side(scene, &sp, shape_node, t);
	init_pl(scene, &pl, flag_shadow);
	detect_hit_disk_top(shape_node, &pl);
	pl.disk_bottom = false;
	if (pl.t > 0)
		if (t <= 0 || pl.t < t)
			t = build_hit_info_cy_disk(scene, shape_node, &pl, flag_shadow);
	detect_hit_disk_bottom(shape_node, &pl);
	pl.disk_bottom = true;
	if (pl.t <= 0)
		return (t);
	if (t <= 0 || pl.t < t)
		t = build_hit_info_cy_disk(scene, shape_node, &pl, flag_shadow);
	return (t);
}
