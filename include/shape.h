/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:00:26 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 12:45:58 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "common.h"

// center = 球の中心
// radius = 球の半径
// normal = 法線ベクトル
typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	t_vec3	normal;
}t_sphere;

// position; 面が通る点の位置ベクトル
typedef struct s_plane
{
	t_vec3	normal;
	t_vec3	position;
}t_plane;

typedef struct s_disk
{
	t_vec3	normal;
	t_vec3	position;
	double	radius;
}t_disk;

typedef struct s_cylinder
{
	t_disk	disk;
	t_disk	disk_bottom;
	t_vec3	center_pos;
	double	radius;
	t_vec3	axis;
	t_vec3	normal;
	double	height;
}t_cylinder;

typedef enum s_t_shape_type
{
	ST_SPHERE,
	ST_PLANE,
	ST_CYLINDER,
}t_shape_type;

// material_color = 物体の色(RGB)
// ambient_ref = 環境光反射率(RGB)
// diffuse_ref = 拡散反射率(RGB)
// specular_ref = 鏡面反射率(RGB)
// shininess = 光沢度
typedef struct s_material
{
	t_fcolor	material_color;
	t_fcolor	ambient_ref;
	t_fcolor	diffuse_ref;
	t_fcolor	specular_ref;
	double		shininess;
}t_material;

// t = 距離の係数t
// material = 物体表面の質感
// hit_pos = 交点の位置ベクトル
typedef struct s_shape
{
	t_shape_type	type;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	}u_obj;
	t_material		material;
	struct s_shape	*next;
	double			t;
	t_vec3			hit_pos;
	t_vec3			hit_pos_normal;
	t_vec3			rot_axis;
	double			rot_angle;
	t_vec3			move_parallel;
	t_vec3			parallel_pos;
	t_vec3			parallel_pos_disk;
	t_vec3			td;
	bool			no_light;
}t_shape;

t_shape	*create_sphere(t_vec3 center, double r, t_ptr_list *alloc_list);
t_shape	*create_plane(t_vec3 normal, t_vec3 position, t_ptr_list *alloc_list);
t_shape	*create_cylinder(\
t_vec3 center, double r, double height, t_ptr_list *alloc_list);

#endif
