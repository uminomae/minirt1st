/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shape.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:37:43 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 16:57:05 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	validate_param_and_identifer_shape(\
char **splited, int param_num, char second_char, int valid_num)
{
	if (splited[0][1] != second_char || splited[0][2] != '\0')
		exit_put_error("Wrong identifier.");
	if (param_num != valid_num)
		exit_put_error("The number of values set is wrong.");
}

static void	validate_position(double z_position, double radius)
{
	if (z_position <= radius)
		exit_put_error("Shape z position too close.");
}

void	set_sphere(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited)
{
	t_vec3			position;
	double			radius;
	t_shape			*sphere;
	const int		param_num = count_splited(splited);
	t_shape_list	*shape_list;

	shape_list = &rtfile->shape_list;
	validate_param_and_identifer_shape(splited, param_num, 'p', 8);
	validate_floating_point_type_array_of_char(splited);
	position = build_vec3(atod(splited[1]), atod(splited[2]), atod(splited[3]));
	radius = atod(splited[4]) / 2;
	validate_position(position.z, radius);
	sphere = create_sphere(position, radius, alloc_list);
	sphere->material.material_color = \
		build_fcolor(atod(splited[5]), atod(splited[6]), atod(splited[7]));
	if (is_proper_rgb_value(sphere->material.material_color) == false)
		exit_put_error("The rgb values are wrong.");
	add_list_shape(shape_list, sphere);
}

void	set_plane(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited)
{
	t_vec3			position;
	t_vec3			norm;
	t_shape			*plane;
	const int		param_num = count_splited(splited);
	t_shape_list	*shape_list;

	shape_list = &rtfile->shape_list;
	validate_param_and_identifer_shape(splited, param_num, 'l', 10);
	validate_floating_point_type_array_of_char(splited);
	position = build_vec3(atod(splited[1]), atod(splited[2]), atod(splited[3]));
	norm = build_vec3(atod(splited[4]), atod(splited[5]), atod(splited[6]));
	if (is_nega_one_to_one(norm) == false)
		exit_put_error("The norm values are wrong.");
	if (is_normalize(norm) == false)
		exit_put_error("Not normalized.");
	plane = create_plane(norm, position, alloc_list);
	plane->material.material_color = \
		build_fcolor(atod(splited[7]), atod(splited[8]), atod(splited[9]));
	if (is_proper_rgb_value(plane->material.material_color) == false)
		exit_put_error("The rgb values are wrong.");
	add_list_shape(shape_list, plane);
}

void	set_cylinder(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited)
{
	t_set_cy		cy;
	t_shape			*cylinder;
	const int		param_num = count_splited(splited);
	t_shape_list	*shape_list;

	shape_list = &rtfile->shape_list;
	validate_param_and_identifer_shape(splited, param_num, 'y', 12);
	validate_floating_point_type_array_of_char(splited);
	ft_memset(&cy, 0, sizeof(t_set_cy));
	cy.position = \
		build_vec3(atod(splited[1]), atod(splited[2]), atod(splited[3]));
	cy.radius = atod(splited[7]) / 2;
	cy.height = atod(splited[8]);
	cylinder = create_cylinder(cy.position, cy.radius, cy.height, alloc_list);
	cylinder->u_obj.cylinder.axis = \
		build_vec3(atod(splited[4]), atod(splited[5]), atod(splited[6]));
	cylinder->material.material_color = \
		build_fcolor(atod(splited[9]), atod(splited[10]), atod(splited[11]));
	validate_position(cy.position.z, cy.radius);
	if (is_proper_rgb_value(cylinder->material.material_color) == false)
		exit_put_error("The rgb values are wrong.");
	add_list_shape(shape_list, cylinder);
}
