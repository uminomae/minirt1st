/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_put_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 09:14:26 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 21:47:16 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	put_vec_rt_format(t_vec3 v, char *s)
{
	printf("\x1b[38;5;198m");
	printf("%s ", s);
	printf("%.2f, ", v.x);
	printf("%.2f, ", v.y);
	printf("%.2f\n", v.z);
	printf("\x1b[0m");
}

void	put_rgb_rt_format(t_fcolor c)
{
	printf("\x1b[38;5;192m");
	printf("%.0f, ", c.red);
	printf("%.0f, ", c.green);
	printf("%.0f\n", c.blue);
	printf("\x1b[0m");
}

void	put_vec(t_vec3 v, char *s)
{
	printf("\x1b[38;5;198m");
	printf("%s :", s);
	printf("x:%.2f, ", v.x);
	printf("y:%.2f, ", v.y);
	printf("z:%.2f\n", v.z);
	printf("\x1b[0m");
}
