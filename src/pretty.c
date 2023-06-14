/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pretty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 10:59:32 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 10:59:36 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	be_harebare_sky_key_p(t_para *para, int keycode)
{
	t_scene	*scene;

	scene = para->scene;
	if (keycode == MAC_OS_KEY_PRETTY)
	{
		rotate_camera(para, 30, 1, 0);
		scene->background_color = build_trgb(1, (int)114, (int)202, (int)253);
		scene->ambient_intensity = build_fcolor(50, 50, 50);
		run_parallel(para);
		return ;
	}
}
