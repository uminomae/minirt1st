/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:34:58 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:39:24 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHADE_H
# define SHADE_H

# include "common.h"

typedef struct s_radiance
{
	t_vec3	l_dir;
	double	incident_angle;
}t_radiance;

typedef struct s_shadow
{
	double	epsilon;
	t_vec3	pi;
	t_vec3	l_dir;
	t_vec3	d;
	t_vec3	el;
}t_shadow;

void		calculate_shade(t_scene *scene, double nearest_t);
bool		is_shadow(t_scene *scene, t_light *light);
t_fcolor	build_radiance_each_light(\
t_scene *scene, t_radiance *rad, t_light *light);
void		calculate_shade_each(\
t_scene *scene, double nearest_t, t_light *light);

#endif