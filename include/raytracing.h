/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:34:58 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 10:15:40 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include "common.h"

typedef struct s_build_screen
{
	double	xs;
	double	ys;
	t_vec3	df;
	t_vec3	dx;
}t_build_screen;

typedef struct s_para
{
	struct s_para	*next;
	t_scene			*scene;
	pthread_mutex_t	*mutex;
	double			y_start;
	double			y_end;
	t_shape			*shape_mouse;
	double			near_t_mouse;
}t_para;

void	build_camera_screen(t_scene *scene, double x, double y);
t_vec3	build_screen(t_build_screen *cm, t_scene *scene, double x, double y);
double	raytracing_each_pixel(t_scene *scene, double x, double y);
void	put_each_pixel(t_mlx *mlx, t_scene *scene, double x, double y);

#endif