/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:51:33 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 15:09:49 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// pe = 𝐩𝐞→ = カメラ・視点位置(eyePosition) = ray.start_pos look from
// m = 𝑚 = カメラからスクリーンまでの距離 = SCREEN_DISTANCE
// df = 𝐝′𝐟→ = (1 / |𝐝𝐟→|) * 𝐝𝐟→ = 正規化した視点から注視点に向かうベクトル 
static t_vec3	build_screen_center_position(t_scene *scene, t_vec3 *df)
{
	const t_vec3	pe = scene->ray.start_pos;
	const double	m = scene->ray.screen_distance;
	const t_vec3	mdf = multiply_vec3(*df, m);
	const t_vec3	pemdf = add_vec3(pe, mdf);

	return (pemdf);
}

// fx = 𝑓𝑥 = (2𝑥𝑠 / 𝑊−1) −1.0 = 正規化したX座標(変換したスクリーン座標のX成分)
// ey = 𝐞𝐲→ = up_dir = 決め打ちの上方向ベクトル = (0,1,0) = view up
// dx = 𝐝𝐱→ = 𝐞𝐲→ * 𝐝′𝐟→ = スクリーン右方向のベクトル
static t_vec3	build_x_screen(\
t_build_screen *b_screen, t_vec3 *ey, double x)
{
	const double	fx = b_screen->xs * x / WIN_WIDTH - (b_screen->xs / 2);
	const t_vec3	dx = calculate_vector_product(*ey, b_screen->df);
	const t_vec3	fxdx = multiply_vec3(dx, fx);

	b_screen->dx = dx;
	return (fxdx);
}

// fy = 𝑓𝑦 = (−2𝑦𝑠 / 𝐻−1) +1.0 = 正規化したY座標(変換したスクリーン座標のY成分)
// dx = 𝐝𝐱→ = 𝐞𝐲→ * 𝐝′𝐟→ = スクリーン右方向のベクトル
// dy = 𝐝𝐲→ = 𝐝′𝐟→ × 𝐝𝐱→ = スクリーン上方向のベクトル
static t_vec3	build_y_screen(t_vec3 *df, t_vec3 *dx, double ys, double y)
{
	const double	fy = -1 * ys * y / WIN_HEIGHT + (ys / 2);
	const t_vec3	dy = calculate_vector_product(*df, *dx);

	return (multiply_vec3(dy, fy));
}

// pw = 𝐩𝐰→ = 𝐩𝐞→ + 𝑚𝐝′𝐟→ + 𝑓𝑥𝐝𝐱→ + 𝑓𝑦𝐝𝐲→ //スクリーン上の点の三次元空間における位置
static t_vec3	build_point_screen(\
const t_vec3 *pemdf, const t_vec3 *fxdx, const t_vec3 *fydy)
{
	t_vec3	pw;

	pw = *pemdf;
	pw = add_vec3(pw, *fxdx);
	pw = add_vec3(pw, *fydy);
	return (pw);
}

t_vec3	build_screen(\
t_build_screen *b_screen, t_scene *scene, double x, double y)
{
	const t_vec3	pemdf = build_screen_center_position(scene, &b_screen->df);
	const t_vec3	fxdx = build_x_screen(b_screen, &scene->ray.view_up, x);
	const t_vec3	fydy = \
		build_y_screen(&b_screen->df, &b_screen->dx, b_screen->ys, y);

	return (build_point_screen(&pemdf, &fxdx, &fydy));
}
