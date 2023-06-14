/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_side.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:49:49 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:10:31 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 円柱の中心位置とカメラ位置の値を原点に平行移動
// parallel_＊　= 平行移動後のベクトル
static void	move_parallel_pos(t_detect_sp *sp, t_shape *shape_node)
{
	const t_vec3	cy_center_pos = shape_node->u_obj.cylinder.center_pos;
	const t_vec3	move = multiply_vec3(cy_center_pos, -1);

	sp->parallel_pos = add_vec3(cy_center_pos, move);
	sp->parallel_s_pos = add_vec3(sp->ray.start_pos, move);
	shape_node->move_parallel = move;
}

// rayを回転する
// rot_＊　= 回転移動後のベクトル
// rotate_angle_axis() = クオータニオンによる回転 ※順回転は第四引数でfalse指定
static void	rotation_ray(t_detect_sp *sp, t_vec3 *axis, double angle)
{
	sp->rot_dir = \
		rotate_angle_axis(*axis, angle, false, sp->ray.direction);
	sp->rot_s_pos = \
		rotate_angle_axis(*axis, angle, false, sp->parallel_s_pos);
}

// 高さを判定する　※回転した状態のまま円柱空間で計算
// rot_hit = 円柱空間座標での交点
static double	case_height_range(\
t_detect_sp *sp, t_shape *shape_node, double t)
{
	const t_vec3	cy_para_pos = shape_node->parallel_pos;
	const double	h = shape_node->u_obj.cylinder.height;	
	const t_vec3	rot_hit = \
						add_vec3(sp->rot_s_pos, multiply_vec3(sp->rot_dir, t));

	if (rot_hit.y < cy_para_pos.y - h / 2 || rot_hit.y > cy_para_pos.y + h / 2)
		t = -1;
	return (t);
}

static double	detect_hit_cylinder_xz(t_detect_sp *sp, double radius)
{
	double	t;
	t_vec3	rot_dir_xz;
	t_vec3	rot_s_xz;

	rot_dir_xz = delete_y_vec3(sp->rot_dir);
	sp->rot_s = subtract_vec3(sp->rot_s_pos, sp->parallel_pos);
	rot_s_xz = delete_y_vec3(sp->rot_s);
	t = build_t_sphere(\
		rot_s_xz, rot_dir_xz, radius);
	return (t);
}

double	detect_hit_cylinder_side(\
t_scene *scene, t_detect_sp *sp, t_shape *shape_node, bool flag_shadow)
{
	double	t;

	init_sp(scene, sp, flag_shadow);
	build_ray_sphere(sp, &shape_node->u_obj.cylinder.center_pos);
	move_parallel_pos(sp, shape_node);
	rotation_ray(sp, &shape_node->rot_axis, shape_node->rot_angle);
	t = detect_hit_cylinder_xz(sp, shape_node->u_obj.cylinder.radius);
	t = case_height_range(sp, shape_node, t);
	return (t);
}
