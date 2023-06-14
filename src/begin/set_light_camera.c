/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_light_camera.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:35:09 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 07:28:06 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	validate_param_and_identifer_camera_light(\
char **splited, int param_num, int valid_num1, int valid_num2)
{
	if (splited[0][1] != '\0')
		exit_put_error("Wrong identifier.");
	if (valid_num2 != -1)
	{
		if (param_num != valid_num1 && param_num != valid_num2)
			exit_put_error("The number of values set is wrong.");
	}
	else
	{
		if (param_num != valid_num1)
			exit_put_error("The number of values set is wrong.");
	}
}

void	set_ambient_light(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited)
{
	t_ambient_light	*amb;
	const int		param_num = count_splited(splited);

	amb = &rtfile->ambient_light;
	validate_param_and_identifer_camera_light(splited, param_num, 5, -1);
	validate_floating_point_type_array_of_char(splited);
	amb->light_ratio = atod(splited[1]);
	if (is_zero_to_one(amb->light_ratio) == false)
		exit_put_error("The light ratio setting values are wrong.");
	amb->ambient_color = \
		build_fcolor(atod(splited[2]), atod(splited[3]), atod(splited[4]));
	if (is_proper_rgb_value(amb->ambient_color) == false)
		exit_put_error("The rgb values are wrong.");
	(void)alloc_list;
}

void	validate_camera_parameters(t_rtfile_camera *camera)
{
	const t_vec3	axis = build_vec3(1, 0, 0);
	const double	radian = -90 * (M_PI / 180);

	camera->view_up = build_vec3(0, 1, 0);
	if (camera->direction.x == 0 && \
		camera->direction.y == -1 && \
		camera->direction.z == 0)
	{
		camera->view_up = \
			rotate_angle_axis(axis, radian, false, camera->direction);
	}
	if (camera->direction.x == 0 && \
		camera->direction.y == 1 && \
		camera->direction.z == 0)
	{
		camera->view_up = \
			rotate_angle_axis(axis, radian, false, camera->direction);
	}
}

void	set_camera(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited)
{
	t_rtfile_camera	*camera;
	const int		param_num = count_splited(splited);

	camera = &rtfile->camera;
	validate_param_and_identifer_camera_light(splited, param_num, 8, -1);
	validate_floating_point_type_array_of_char(splited);
	camera->start_pos = \
		build_vec3(atod(splited[1]), atod(splited[2]), atod(splited[3]));
	camera->direction = \
		build_vec3(atod(splited[4]), atod(splited[5]), atod(splited[6]));
	if (is_nega_one_to_one(camera->direction) == false)
		exit_put_error("The camera direction values are wrong.");
	if (is_normalize(camera->direction) == false)
		exit_put_error("Not normalized.");
	validate_camera_parameters(camera);
	camera->fov = atod(splited[7]);
	if (camera->fov < 0 || camera->fov > 180)
		exit_put_error("fov is out of range.");
	if (camera->start_pos.z > -1)
		exit_put_error("Camera z position too close.");
	(void)alloc_list;
}

void	set_light(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited)
{
	t_vec3			pos;
	double			brightness_ratio;
	t_fcolor		color;
	const int		param_num = count_splited(splited);
	t_light_list	*light_list;

	light_list = &rtfile->light_list;
	validate_param_and_identifer_camera_light(splited, param_num, 5, 8);
	validate_floating_point_type_array_of_char(splited);
	pos = build_vec3(atod(splited[1]), atod(splited[2]), atod(splited[3]));
	brightness_ratio = atod(splited[4]);
	if (is_zero_to_one(brightness_ratio) == false)
		exit_put_error("The light ratio setting values are wrong.");
	if (param_num == NO_COLOR_SPECIFIED)
		color = build_fcolor(255, 255, 255);
	if (param_num == COLOR_SPECIFIED)
		color = \
			build_fcolor(atod(splited[5]), atod(splited[6]), atod(splited[7]));
	if (is_proper_rgb_value(color) == false)
		exit_put_error("The rgb values are wrong.");
	add_list_light(light_list, \
			create_light(alloc_list, pos, brightness_ratio, color));
}
