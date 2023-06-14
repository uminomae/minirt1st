/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:34:58 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:37:38 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

# include "common.h"

typedef struct s_quaternion
{
	double	w;
	double	x;
	double	y;
	double	z;
}t_quaternion;

typedef struct s_detect_sp
{
	double	t;
	t_ray	ray;
	t_vec3	s_pos;
	t_vec3	parallel_s_pos;
	t_vec3	parallel_pos;
	t_vec3	rot_s_pos;
	t_vec3	s;
	t_vec3	rot_s;
	t_vec3	parallel_s;
	t_vec3	dir;
	t_vec3	rot_dir;
	t_vec3	pc;
	double	r;
	t_vec3	m;
	t_vec3	p;
}t_detect_sp;

typedef struct s_detect_pl
{
	double	t;
	t_ray	ray;
	t_vec3	s_pos;
	t_vec3	parallel_s_pos;
	t_vec3	parallel_pos_disk;
	t_vec3	rot_s_pos;
	t_vec3	s;
	t_vec3	rot_s;
	t_vec3	parallel_s;
	t_vec3	dir;
	t_vec3	rot_dir;
	t_vec3	pos;
	t_vec3	obj_pos;
	t_vec3	normal;
	bool	disk_bottom;
}t_detect_pl;

void			init_pl(\
t_scene *scene, t_detect_pl *pl, bool flag_shadow);
void			build_ray_plane(t_detect_pl *pl, t_vec3 obj_pos);
double			detect_hit_of_plane(\
t_scene *scene, t_shape *shape, bool flag_shadow);

void			init_sp(\
t_scene *scene, t_detect_sp *sp, bool flag_shadow);
void			build_ray_sphere(t_detect_sp *sp, const t_vec3 *obj_pos);
double			build_t_sphere(t_vec3 s, t_vec3 dir, double r);
double			detect_hit_of_sphere(\
t_scene *scene, t_shape *shape, bool flag_shadow);

double			detect_hit_of_cylinder(\
t_scene *scene, t_shape *shape, bool flag_shadow);
double			detect_hit_cylinder_disk(t_detect_pl *pl, t_shape *shape);

void			build_hit_info_cy_side(\
t_scene *scene, t_detect_sp *sp, t_shape *shape, double t);
double			detect_hit_cylinder_side(\
t_scene *scene, t_detect_sp *sp, t_shape *shape, bool flag_shadow);
t_vec3			rotate_angle_axis(\
t_vec3 axis, double radian, bool inverse, t_vec3 obj);

void			build_hit_info(t_scene *scene, t_shape *shape, double t);
t_vec3			build_hit_pos(t_scene *scene, double t);
double			hit_nearest(t_scene *scene, bool flag_shadow);
// rot
t_quaternion	build_quaternion(double w, double x, double y, double z);
t_vec3			quaternion_to_vec3(t_quaternion qua);
t_quaternion	quaternion_mult(t_quaternion q1, t_quaternion q2);

#endif