/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_disk.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:49:49 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:37:19 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 円柱の中心位置とカメラ位置の値を原点に平行移動
// parallel_＊　= 平行移動後のベクトル
static void	move_parallel_pos_disk(\
t_detect_pl *pl, t_shape *shape, t_vec3 disk_pos)
{
	const t_vec3	move = shape->move_parallel;

	pl->parallel_pos_disk = add_vec3(disk_pos, move);
	pl->parallel_s_pos = add_vec3(pl->ray.start_pos, move);
}

// rayを回転する
// rot_＊　= 回転移動後のベクトル
// rotate_angle_axis() = クオータニオンによる回転 ※順回転は第四引数でfalse指定
static void	rotation_ray_disk(t_detect_pl *pl, t_vec3 axis, double angle)
{
	pl->rot_dir = \
		rotate_angle_axis(axis, angle, false, pl->ray.direction);
	pl->rot_s_pos = \
		rotate_angle_axis(axis, angle, false, pl->parallel_s_pos);
}

// 円柱空間座標で交点を計算
double	build_t_disk(t_detect_pl *pl)
{
	const t_vec3	s = subtract_vec3(pl->rot_s_pos, pl->parallel_pos_disk);
	const double	d_n_dot = calculate_scalar_product(pl->rot_dir, pl->normal);
	const double	s_n_dot = calculate_scalar_product(s, pl->normal);
	const double	t = (-1 * s_n_dot) / d_n_dot;

	pl->rot_s = s;
	return (t);
}

// 半径外にある場合t=-1にする
// 円柱空間座標で計算
static void	validate_inside(t_detect_pl *pl, t_shape *shape)
{
	const t_vec3	rot_hit = \
		add_vec3(pl->rot_s, multiply_vec3(pl->rot_dir, pl->t));
	const t_vec3	hit_diff = subtract_vec3(rot_hit, shape->parallel_pos_disk);
	const double	r = shape->u_obj.cylinder.disk.radius;

	if (calculate_norm_vec3(hit_diff) > r)
		pl->t = -1;
}

double	detect_hit_cylinder_disk(t_detect_pl *pl, t_shape *shape)
{
	const t_vec3	obj_pos = pl->obj_pos;

	build_ray_plane(pl, obj_pos);
	move_parallel_pos_disk(pl, shape, obj_pos);
	rotation_ray_disk(pl, shape->rot_axis, shape->rot_angle);
	pl->t = build_t_disk(pl);
	validate_inside(pl, shape);
	return (pl->t);
}
