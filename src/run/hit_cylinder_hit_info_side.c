/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cylinder_hit_info.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:49:49 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 16:27:23 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// p = 交点
// tmp_n = 円柱空間座標の法線
// hit_pos_normal = ワールド空間座標の交点の法線
static t_vec3	build_hit_pos_normal(\
t_shape *shape, t_vec3 rot_s_pos, t_vec3 td)
{
	const t_vec3	p = add_vec3(rot_s_pos, td);
	const t_vec3	cy_pos_origin = shape->parallel_pos;
	t_vec3			tmp_n;
	t_vec3			hit_pos_normal;

	tmp_n.x = 2 * (p.x - cy_pos_origin.x);
	tmp_n.y = 0;
	tmp_n.z = 2 * (p.z - cy_pos_origin.z);
	hit_pos_normal = rotate_angle_axis(\
				shape->rot_axis, shape->rot_angle * -1, false, tmp_n);
	return (hit_pos_normal);
}

// hit_pos_normal = ワールド空間座標の交点の法線 ※ワールド空間に戻すためにangleを逆にして回転
// hit_pos = ワールド空間座標の交点の位置ベクトル
void	build_hit_info_cy_side(\
t_scene *scene, t_detect_sp *sp, t_shape *shape, double t)
{
	shape->td = multiply_vec3(sp->rot_dir, t);
	shape->hit_pos_normal = \
			build_hit_pos_normal(shape, sp->rot_s_pos, shape->td);
	shape->hit_pos = build_hit_pos(scene, t);
}
