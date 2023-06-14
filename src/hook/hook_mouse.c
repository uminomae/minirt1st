/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:50:33 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 22:54:36 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ウィンドウの上下左右のエリアをクリックすることで、クリックした位置の方向へ回転する
// 最小化しないと機能しない場合がある。
static bool	rot_cam_mouse(t_para *para, int x_pos, int y_pos)
{
	const int	top_border = (WIN_HEIGHT / 3);
	const int	bottom_border = WIN_HEIGHT - (WIN_HEIGHT / 3);
	const int	left_border = (WIN_WIDTH / 3);
	const int	right_border = WIN_WIDTH - (WIN_WIDTH / 3);

	if (y_pos < 0)
		return (false);
	else if (y_pos < top_border && \
		left_border < x_pos && x_pos < right_border)
		rotate_camera(para, 15, 1, 0);
	else if (bottom_border < y_pos && \
			left_border < x_pos && x_pos < right_border)
		rotate_camera(para, -15, 1, 0);
	else if (x_pos < left_border && \
			top_border < y_pos && y_pos < bottom_border)
		rotate_camera(para, 15, 0, 1);
	else if (right_border < x_pos & \
			top_border < y_pos && y_pos < bottom_border)
		rotate_camera(para, -15, 0, 1);
	else
		return (false);
	return (true);
}

// 右クリックでt_shape*を取得する。球と円柱以外は取得しない。
static void	pick_move_obj_mouse(t_para *para, int x_pos, int y_pos)
{
	double	t;

	para->shape_mouse = NULL;
	printf("reset shape\n");
	t = raytracing_each_pixel(para->scene, x_pos, y_pos);
	if (t <= 0)
		return ;
	if (para->scene->near_shape->type != ST_SPHERE && \
		para->scene->near_shape->type != ST_CYLINDER)
		return ;
	para->shape_mouse = para->scene->near_shape;
	para->near_t_mouse = t;
	printf("got the obj ");
	printf("type: %d\n", para->shape_mouse->type);
	return ;
}

int	operate_with_mouse(int mouse, int x_m_pos, int y_m_pos, t_para *para)
{
	bool	run;
	t_scene	*scene;

	scene = para->scene;
	run = false;
	if (mouse == MOUSE_LEFT)
		run = rot_cam_mouse(para, x_m_pos, y_m_pos);
	else if (mouse == MOUSE_RIGHT)
		pick_move_obj_mouse(para, x_m_pos, y_m_pos);
	else if (mouse == MOUSE_SCROLL_UP)
		zoom_camera(&scene->ray.fov, -10, &run);
	else if (mouse == MOUSE_SCROLL_DOWN)
		zoom_camera(&scene->ray.fov, 10, &run);
	if (run)
		run_parallel(para);
	return (0);
}
