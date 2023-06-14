/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:47:46 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:20:00 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_fcolor	build_fcolor(double r, double g, double b)
{
	t_fcolor	ret;

	ret.red = r;
	ret.green = g;
	ret.blue = b;
	return (ret);
}

int	build_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b << 0);
}

t_fcolor	multiply_fcolor(t_fcolor a, t_fcolor ratio)
{
	t_fcolor	c;

	c.red = a.red * ratio.red;
	c.green = a.green * ratio.green;
	c.blue = a.blue * ratio.blue;
	return (c);
}

t_fcolor	add_fcolor(t_fcolor a, t_fcolor b)
{
	t_fcolor	c;

	c.red = a.red + b.red;
	c.green = a.green + b.green;
	c.blue = a.blue + b.blue;
	return (c);
}

t_fcolor	multiply_fcolor_double(t_fcolor a, double k)
{
	t_fcolor	c;

	c.red = a.red * k;
	c.green = a.green * k;
	c.blue = a.blue * k;
	return (c);
}
