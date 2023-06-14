/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_quaternion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:46:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:11:39 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_quaternion	build_quaternion(double w, double x, double y, double z)
{
	t_quaternion	qua;

	qua.w = w;
	qua.x = x;
	qua.y = y;
	qua.z = z;
	return (qua);
}

t_vec3	quaternion_to_vec3(t_quaternion qua)
{
	t_vec3	v;

	v.x = qua.x;
	v.y = qua.y;
	v.z = qua.z;
	return (v);
}

t_quaternion	quaternion_mult(t_quaternion q1, t_quaternion q2)
{
	t_quaternion	ret;

	ret.w = q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z;
	ret.x = q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y;
	ret.y = q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x;
	ret.z = q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w;
	return (ret);
}
