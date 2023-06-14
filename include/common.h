/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:59:25 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:14:07 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H

# include <stdio.h>
# include <math.h>
# include <libc.h>
# include "mlx.h"
# include "libft.h"
# include <stdbool.h>
# include <pthread.h>

# define MULTI_SP

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		bits_per_pixel;
	int		line_size;
	int		endian;
	char	*img_data;
}t_mlx;

typedef struct s_vec3 {
	double	x;
	double	y;
	double	z;
}t_vec3;

typedef struct s_fcolor {
	double	red;
	double	green;
	double	blue;
}t_fcolor;

#endif
