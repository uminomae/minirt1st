/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_plane.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:51:50 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:36:15 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//----------------------------------
// Plane intersection detection
//----------------------------------

// scene->ray.start_pos = カメラの位置
// scene->ray.direction = カメラからスクリーン画素への方向ベクトル（norm = 1）
// scene->shadow_ray.start_pos = 物体とカメラの交点 
// scene->shadow_ray.direction = 物体から光源への方向ベクトル（norm = 1）
void	init_pl(t_scene *scene, t_detect_pl *pl, bool flag_shadow)
{
	ft_memset(pl, 0, sizeof(t_detect_pl));
	pl->ray = scene->ray;
	if (flag_shadow == true)
		pl->ray = scene->shadow_ray;
}

void	build_ray_plane(t_detect_pl *pl, t_vec3 obj_pos)
{
	pl->dir = pl->ray.direction;
	pl->s_pos = pl->ray.start_pos;
	pl->s = subtract_vec3(pl->ray.start_pos, obj_pos);
}

// d_n_dot = (𝐝⃗ ⋅𝐧⃗ )　= 方向と法線の内積
// s_n_dot = (𝐬⃗ ⋅𝐧⃗) 
static double	build_t_plane(t_detect_pl *pl)
{
	double	d_n_dot;
	double	s_n_dot;
	double	t;

	d_n_dot = calculate_scalar_product(pl->dir, pl->normal);
	if (d_n_dot == 0)
		return (-1);
	s_n_dot = calculate_scalar_product(pl->s, pl->normal);
	t = (-1 * s_n_dot) / d_n_dot;
	return (t);
}

// nomal = 法線node->u_obj.plane.normal;
double	detect_hit_of_plane(t_scene *scene, t_shape *shape, bool flag_shadow)
{
	t_detect_pl		pl;
	const t_vec3	obj_pos = shape->u_obj.plane.position;

	init_pl(scene, &pl, flag_shadow);
	build_ray_plane(&pl, obj_pos);
	pl.normal = shape->u_obj.plane.normal;
	pl.t = build_t_plane(&pl);
	if (flag_shadow == false)
		build_hit_info(scene, shape, pl.t);
	return (pl.t);
}
