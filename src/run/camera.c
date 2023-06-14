/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:50:22 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 22:58:43 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_cam(t_build_screen *camera)
{
	ft_memset(camera, 0, sizeof(t_build_screen));
}

// radian_fov = 視野角（ラジアン・弧度法）
// h =  スクリーンサイズの補正係数
// xs = スクリーンの幅
// xh = スクリーンの高さ
static void	build_screen_fov_angle(t_build_screen *b_screen, t_scene *scene)
{
	const double	radian_fov = scene->ray.fov * (M_PI / 180);
	const double	h = tan(radian_fov / 2);

	b_screen->xs = scene->screen_width * h;
	b_screen->ys = scene->screen_height * h;
}

// 𝐩𝐭→ = 注視点の位置 = lookAt
// tmp_df = 𝐝𝐟→ = forward_dir = 𝐩𝐭→ – 𝐩𝐞→ = 視点から注視点に向かうベクトル
// tmp_df_norm = tmp_df のノルム
// df = 𝐝′𝐟→ = (1 / |𝐝𝐟→|) * 𝐝𝐟→ = 正規化した視点から注視点に向かうベクトル 
static t_vec3	build_camera_to_look_at(
const t_vec3 *s_pos, const t_vec3 *look_at)
{
	const t_vec3	pt = add_vec3(*s_pos, *look_at);
	const t_vec3	tmp_df = subtract_vec3(pt, *s_pos);
	const double	tmp_df_norm = calculate_norm_vec3(tmp_df);
	const t_vec3	df = multiply_vec3(tmp_df, (1 / tmp_df_norm));

	return (df);
}

// df = 𝐝′𝐟→ = (1 / |𝐝𝐟→|) * 𝐝𝐟→ = 正規化した視点から注視点に向かうベクトル 
// pw = 𝐩𝐰→ = 𝐩𝐞→ + 𝑚𝐝′𝐟→ + 𝑓𝑥𝐝𝐱→ + 𝑓𝑦𝐝𝐲→ //スクリーン上の点の三次元空間における位置
void	build_camera_screen(t_scene *scene, double x, double y)
{
	const t_vec3	*s_pos = &scene->ray.start_pos;
	const t_vec3	*look_at = &scene->ray.look_at;
	t_build_screen	b_screen;
	t_vec3			pw;

	init_cam(&b_screen);
	build_screen_fov_angle(&b_screen, scene);
	b_screen.df = build_camera_to_look_at(s_pos, look_at);
	pw = build_screen(&b_screen, scene, x, y);
	scene->camera_to_screen = subtract_vec3(pw, *s_pos);
	scene->ray.direction = normalize_vec3(scene->camera_to_screen);
}
