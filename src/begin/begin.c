/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:51:10 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 05:26:57 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_struct(\
t_ptr_list *alloc_list, t_scene *scene, t_rtfile *rtfile)
{
	ft_memset(alloc_list, 0, sizeof(t_ptr_list));
	ft_memset(scene, 0, sizeof(t_scene));
	ft_memset(rtfile, 0, sizeof(t_rtfile));
}

static void	init_mlx(t_mlx *mlx)
{
	ft_memset(mlx, 0, sizeof(t_mlx));
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, TITLE);
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx->bits_per_pixel = 32;
	mlx->img_data = mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_pixel, \
										&mlx->line_size, &mlx->endian);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 0, 0);
}

// ia = 𝐼𝑎 = ambient_intensity = 環境光の強度
static t_fcolor	build_ambient_light_intensity_scene(t_scene *scene)
{
	const double	ratio = scene->ambient_ref_ratio;
	const t_fcolor	color = scene->ambient_ref_color;
	const t_fcolor	tmp_color = multiply_fcolor_double(color, 1.0f / 255.0f);
	const t_fcolor	ia = multiply_fcolor_double(tmp_color, ratio);

	return (ia);
}

static void	set_scene(t_rtfile *rtfile, t_scene *scene)
{
	double	aspect_ratio;

	scene->ambient_ref_ratio = rtfile->ambient_light.light_ratio;
	scene->ambient_ref_color = rtfile->ambient_light.ambient_color;
	scene->ambient_intensity = build_ambient_light_intensity_scene(scene);
	scene->ray.start_pos = rtfile->camera.start_pos;
	scene->ray.look_at = rtfile->camera.direction;
	scene->ray.fov = rtfile->camera.fov;
	scene->ray.view_up = rtfile->camera.view_up;
	scene->ray.screen_distance = SCREEN_DISTANCE;
	scene->light_list = rtfile->light_list;
	scene->shape_list = rtfile->shape_list;
	aspect_ratio = (double)WIN_HEIGHT / (double)WIN_WIDTH;
	scene->screen_width = SCREEN_WIDTH;
	scene->screen_height = SCREEN_WIDTH * aspect_ratio;
	scene->background_color = build_trgb(1, (int)200, (int)200, (int)200);
	scene->y_axis = build_vec3(0, 1, 0);
}

void	begin_minirt(\
t_mlx *mlx, t_ptr_list *alloc_list, char *file_name, t_scene *scene)
{
	t_rtfile	rtfile;

	init_struct(alloc_list, scene, &rtfile);
	read_rtfile(&rtfile, alloc_list, file_name);
	init_mlx(mlx);
	set_scene(&rtfile, scene);
}
