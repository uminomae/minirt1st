/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:50:37 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 05:26:11 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "common.h"
# include "shape.h"

typedef struct s_ray
{
	t_vec3	start_pos;
	t_vec3	direction;
	t_vec3	look_at;
	double	fov;
	t_vec3	view_up;
	double	screen_distance;
}t_ray;

typedef enum s_t_light_type
{
	LT_POINT,
}t_light_type;

typedef struct s_light
{
	struct s_light	*next;
	t_light_type	type;
	t_vec3			position;
	double			brightness_ratio;
	t_fcolor		color;
	t_fcolor		light_intensity;
}t_light;

typedef struct s_light_list
{
	struct s_light	*head;
	struct s_light	*tail;
}t_light_list;

typedef struct s_shape_list
{
	struct s_shape	*head;
	struct s_shape	*tail;
}t_shape_list;

typedef struct s_scene
{
	struct s_scene	*next;
	t_shape			*near_shape;
	t_light_list	light_list;
	t_shape_list	shape_list;
	t_vec3			screen_vec;
	t_vec3			camera_to_screen;
	t_ray			ray;
	t_ray			shadow_ray;
	double			nearest_t;
	t_fcolor		radiance_all;
	double			ambient_ref_ratio;
	t_fcolor		ambient_ref_color;
	int				background_color;
	t_fcolor		ambient_intensity;
	double			screen_width;
	double			screen_height;
	t_ptr_list		*alloc_list;
	t_mlx			*mlx;
	pthread_mutex_t	*mutex;
	t_vec3			y_axis;
}t_scene;

#endif
