/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:11:33 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 22:55:13 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	validate_floating_point_type_array_of_char(char **splited)
{
	size_t	i;

	i = 1;
	while (splited[i])
	{
		if (is_number(splited[i]) == false)
			exit_put_error("An incorrect non-numeric value was detected.");
		i++;
	}
}

bool	is_nega_one_to_one(t_vec3 v)
{
	if (v.x < -1 || 1 < v.x)
		return (false);
	if (v.y < -1 || 1 < v.y)
		return (false);
	if (v.z < -1 || 1 < v.z)
		return (false);
	return (true);
}

bool	is_zero_to_one(double num)
{
	return (0 <= num && num <= 1);
}

bool	is_proper_rgb_value(t_fcolor colors)
{
	if (colors.blue < 0 || 255 < colors.blue)
		return (false);
	if (colors.green < 0 || 255 < colors.green)
		return (false);
	if (colors.red < 0 || 255 < colors.red)
		return (false);
	return (true);
}

bool	is_number(const char *str)
{
	bool	flag_decimal_poit;
	size_t	i;

	i = 0;
	flag_decimal_poit = false;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] == '.')
		{
			if (flag_decimal_poit)
				return (false);
			flag_decimal_poit = true;
		}
		else if (ft_isdigit(str[i]) == false)
			return (false);
		i++;
	}
	if (i == 1 && (str[0] == '-' || str[0] == '.'))
		return (false);
	if (i == 2 && str[0] == '-' && str[1] == '.')
		return (false);
	return (true);
}
