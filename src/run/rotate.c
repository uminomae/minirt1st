/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 17:46:51 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 21:04:19 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// axis    回転させる軸　単位ベクトル
// radian  回転させる角度(ラジアン)
static t_quaternion	make_quaternion(t_vec3 axis, double radian)
{
	t_quaternion	qua;

	qua.w = cos(radian / 2);
	qua.x = axis.x * sin(radian / 2);
	qua.y = axis.y * sin(radian / 2);
	qua.z = axis.z * sin(radian / 2);
	return (qua);
}

static void	inverse_quaternion(t_quaternion *qua, t_quaternion *conjugate)
{
	qua->x *= -1;
	qua->y *= -1;
	qua->z *= -1;
	conjugate->x *= -1;
	conjugate->y *= -1;
	conjugate->z *= -1;
}

// axis = 回転の軸
// radian = 回転させる角度
// inverse = trueで逆回転、falseで順回転
// obj = 回転させるオブジェクトの座標
t_vec3	rotate_angle_axis(\
t_vec3 axis, double radian, bool inverse, t_vec3 obj)
{
	t_quaternion	qua;
	t_quaternion	conjugate;
	t_quaternion	pos;

	pos = build_quaternion(0, obj.x, obj.y, obj.z);
	if (axis.x == 0 && axis.y == 0 && axis.z == 0)
		return (obj);
	if (radian == 0)
		return (obj);
	qua = make_quaternion(axis, radian);
	conjugate = make_quaternion(axis, -radian);
	if (inverse)
		inverse_quaternion(&qua, &conjugate);
	pos = quaternion_mult(qua, pos);
	pos = quaternion_mult(pos, conjugate);
	return (quaternion_to_vec3(pos));
}
