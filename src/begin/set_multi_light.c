/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_multi_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:35:09 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 17:01:51 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	validate_param_and_identifer_multi_color_light(\
char **splited, int param_num, int valid_num1, int valid_num2)
{
	if (splited[0][1] != 'L' || splited[0][2] != '\0')
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

void	set_multi_light(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited)
{
	t_vec3			pos;
	double			brightness_ratio;
	t_fcolor		color;
	const int		param_num = count_splited(splited);
	t_light_list	*light_list;

	light_list = &rtfile->light_list;
	validate_param_and_identifer_multi_color_light(splited, param_num, 5, 8);
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
