/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook_cam_light.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:50:33 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/12 16:49:33 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// ↑ : look_at.y++, view_up.y++
// ↓ : look_at.y--, view_up.y--
// ← : look_at.x--, view_up.x--
// → : look_at.x++, view_up.y++
static void	operate_with_allow_keys(t_para *para, int keycode)
{
	t_scene	*scene;

	scene = para->scene;
	if (keycode == MAC_OS_KEY_UP)
		move_camera(&scene->ray.start_pos.y, 1);
	else if (keycode == MAC_OS_KEY_DOWN)
		move_camera(&scene->ray.start_pos.y, -1);
	else if (keycode == MAC_OS_KEY_LEFT)
		move_camera(&scene->ray.start_pos.x, -1);
	else if (keycode == MAC_OS_KEY_RIGHT)
		move_camera(&scene->ray.start_pos.x, 1);
	else
		return ;
	run_parallel(para);
}

// x : light x++
// y : light y++
// z : light z++
// q : light x--
// w : light y--
// e : light z--
static void	operate_with_alphabet_keys_light(t_para *para, int keycode)
{
	t_scene	*scene;
	bool	valid;

	scene = para->scene;
	valid = false;
	if (keycode == MAC_OS_KEY_X)
		valid = move_light(scene->light_list.head, 1, 0, 0);
	else if (keycode == MAC_OS_KEY_Y)
		valid = move_light(scene->light_list.head, 0, 1, 0);
	else if (keycode == MAC_OS_KEY_Z)
		valid = move_light(scene->light_list.head, 0, 0, 1);
	else if (keycode == MAC_OS_KEY_Q)
		valid = move_light(scene->light_list.head, -1, 0, 0);
	else if (keycode == MAC_OS_KEY_W)
		valid = move_light(scene->light_list.head, 0, -1, 0);
	else if (keycode == MAC_OS_KEY_E)
		valid = move_light(scene->light_list.head, 0, 0, -1);
	else
		return ;
	if (valid)
		run_parallel(para);
}

// i : zoom(fov) in
// o : zoom(fov) out
// u : look at up
// d : look at down
// l : look at left
// r : look at right
static void	operate_with_alphabet_keys(t_para *para, int keycode)
{
	t_scene	*scene;
	bool	run;

	scene = para->scene;
	run = true;
	if (keycode == MAC_OS_KEY_I)
		zoom_camera(&scene->ray.fov, -10, &run);
	else if (keycode == MAC_OS_KEY_O)
		zoom_camera(&scene->ray.fov, 10, &run);
	else if (keycode == MAC_OS_KEY_U)
		rotate_camera(para, 15, 1, 0);
	else if (keycode == MAC_OS_KEY_D)
		rotate_camera(para, -15, 1, 0);
	else if (keycode == MAC_OS_KEY_L)
		rotate_camera(para, 15, 0, 1);
	else if (keycode == MAC_OS_KEY_R)
		rotate_camera(para, -15, 0, 1);
	else
		return ;
	if (run)
		run_parallel(para);
}

int	operate_with_key(int keycode, t_para *para)
{
	if (keycode == MAC_OS_KEY_ESC)
		close_window(para->scene);
	operate_with_allow_keys(para, keycode);
	operate_with_alphabet_keys(para, keycode);
	operate_with_alphabet_keys_light(para, keycode);
	operate_with_num_keys_sp(para, keycode);
	operate_with_num_keys_cy(para, keycode);
	operate_with_num_keys_material(para, keycode);
	be_harebare_sky_key_p(para, keycode);
	return (0);
}
