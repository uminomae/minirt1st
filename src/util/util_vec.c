/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_vec.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:14:26 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 21:47:45 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec3	build_vec3(double x, double y, double z)
{
	t_vec3	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec3	add_vec3(t_vec3 a, t_vec3 b)
{
	return (build_vec3(a.x + b.x, a.y + b.y, a.z + b.z));
}

t_vec3	subtract_vec3(t_vec3 a, t_vec3 b)
{
	return (build_vec3(a.x - b.x, a.y - b.y, a.z - b.z));
}

// ベクトルのスカラー倍
t_vec3	multiply_vec3(t_vec3 a, double b)
{
	return (build_vec3(a.x * b, a.y * b, a.z * b));
}
