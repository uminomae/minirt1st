/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 00:00:54 by uminomae          #+#    #+#             */
/*   Updated: 2023/05/28 00:10:54 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	count_splited(char **splited)
{
	int	ret;

	ret = 0;
	while (splited[ret])
		ret++;
	return (ret);
}

typedef struct s_atod
{
	double	int_part;
	double	fractional_part;
	double	factor;
	int		sign;
}t_atod;

void	init_atod(t_atod *d)
{
	ft_memset(d, 0, sizeof(t_atod));
	d->sign = 1;
	d->factor = 0.1;
}

double	atod(const char *str)
{
	t_atod	d;

	init_atod(&d);
	if (*str == '-')
	{
		d.sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		d.int_part = d.int_part * 10.0 + (*str - '0');
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			d.fractional_part = d.fractional_part + d.factor * (*str - '0');
			d.factor /= 10.0;
			str++;
		}
	}
	return (d.sign * (d.int_part + d.fractional_part));
}
