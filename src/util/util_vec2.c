/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_vec2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:25:04 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:10:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ベクトルのノルムを返す
double	calculate_norm_vec3(t_vec3 a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

// ベクトルのノルムを１にする
t_vec3	normalize_vec3(t_vec3 a)
{
	const double	mag = calculate_norm_vec3(a);

	return (build_vec3(a.x / mag, a.y / mag, a.z / mag));
}

// ベクトルの内積
double	calculate_scalar_product(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

// ベクトルの外積
t_vec3	calculate_vector_product(t_vec3 a, t_vec3 b)
{
	t_vec3	vec;

	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x * b.z;
	vec.z = a.x * b.y - a.y * b.x;
	return (vec);
}

// 円柱の側面の交差判定時にyをゼロにする
t_vec3	delete_y_vec3(t_vec3 a)
{
	return (build_vec3(a.x, 0, a.z));
}
