/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:11:33 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 22:56:24 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_normalize(t_vec3 vec)
{
	const double	norm = calculate_norm_vec3(vec);

	return (0.99 < norm && norm < 1.01);
}
