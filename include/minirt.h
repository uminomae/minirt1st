/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 13:54:29 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/11 21:59:34 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "common.h"

# include "alloc.h"
# include "begin.h"
# include "raytracing.h"
# include "scene.h"
# include "shape.h"
# include "hit.h"
# include "shade.h"

# define TITLE	"miniRT"

# define WIN_WIDTH			360
# define WIN_HEIGHT			360
# define NUM_OF_THREADS		36
# define PARA_ARRAY			37
# define AMOUNT_OF_ROWS		10

// # define WIN_WIDTH		800
// # define WIN_HEIGHT		800
// # define NUM_OF_THREADS		36
// # define PARA_ARRAY			37
// # define AMOUNT_OF_ROWS		22

# define SCREEN_WIDTH		2

# define REVERSE_DIRECTION -1
# define SCREEN_DISTANCE	1

# define MAC_OS_KEY_ESC		53
# define MAC_OS_KEY_LEFT	123
# define MAC_OS_KEY_UP		126
# define MAC_OS_KEY_RIGHT	124
# define MAC_OS_KEY_DOWN	125

# define MAC_OS_KEY_1		18
# define MAC_OS_KEY_2		19
# define MAC_OS_KEY_3		20
# define MAC_OS_KEY_4		21
# define MAC_OS_KEY_5		23
# define MAC_OS_KEY_6		22
# define MAC_OS_KEY_7		26
# define MAC_OS_KEY_8		28
# define MAC_OS_KEY_9		25

# define MAC_OS_KEY_A		0
# define MAC_OS_KEY_B		11
# define MAC_OS_KEY_C		8
# define MAC_OS_KEY_D		2
# define MAC_OS_KEY_E		14
# define MAC_OS_KEY_G		5
# define MAC_OS_KEY_I		34
# define MAC_OS_KEY_J		38
# define MAC_OS_KEY_L		37
# define MAC_OS_KEY_K		40
# define MAC_OS_KEY_O		31
# define MAC_OS_KEY_PRETTY	35
# define MAC_OS_KEY_Q		12
# define MAC_OS_KEY_R		15
# define MAC_OS_KEY_U		32
# define MAC_OS_KEY_W		13
# define MAC_OS_KEY_X		7
# define MAC_OS_KEY_Y		16
# define MAC_OS_KEY_Z		6

# define MOUSE_LEFT			1
# define MOUSE_RIGHT		2
# define MOUSE_SCROLL_UP	4
# define MOUSE_SCROLL_DOWN	5
# define ON_EXPOSE			12
# define ON_DESTROY			17

# define AMBIENT_R			1.0f
# define DIFFUSE_R			0.69f
# define SPECULAR_R			0.2f
# define CY_SPECULAR_R		0.01f
# define SHININESS			50
# define CY_SHININESS		2

# define SAME_STR			0
# define NOT_FOUND			-1
# define NO_COLOR_SPECIFIED	5
# define COLOR_SPECIFIED	8
# define NEWLINE			-1
# define SUCCESS			0
# define NONE				-1
# define REQUIRED_IDENTIFIERS 3

void		validate_arg(int argc, char **argv);
int			run_raytracer(t_mlx *mlx, t_scene *scene);
//end
void		exit_put_perror(char *s);
void		exit_put_error(char *s);
//color
int			build_trgb(int t, int r, int g, int b);
t_fcolor	build_fcolor(double r, double g, double b);
t_fcolor	multiply_fcolor(t_fcolor a, t_fcolor ratio);
t_fcolor	add_fcolor(t_fcolor a, t_fcolor b);
t_fcolor	multiply_fcolor_double(t_fcolor a, double k);
//util vec
void		put_vec(t_vec3 v, char *s);
void		put_vec_rt_format(t_vec3 v, char *s);
void		put_rgb_rt_format(t_fcolor c);
t_vec3		build_vec3(double x, double y, double z);
t_vec3		subtract_vec3(t_vec3 a, t_vec3 b);
double		calculate_norm_vec3(t_vec3 a);
t_vec3		normalize_vec3(t_vec3 a);
t_vec3		normalize_vec3(t_vec3 a);
double		calculate_scalar_product(t_vec3 a, t_vec3 b);
t_vec3		add_vec3(t_vec3 a, t_vec3 b);
t_vec3		multiply_vec3(t_vec3 a, double b);
t_vec3		delete_y_vec3(t_vec3 a);
t_vec3		calculate_vector_product(t_vec3 a, t_vec3 b);
char		*get_next_line(int fd);
//hook
void		hook_mlx(\
t_mlx *mlx, t_scene *scene, t_ptr_list *alloc_list, t_para *para);
int			operate_with_mouse(\
int mouse, int x_m_pos, int y_m_pos, t_para *para);
void		*raytracing_in_parallel(void *para);
void		run_parallel(t_para *para);
bool		move_light(t_light *light, int add_x, int add_y, int add_z);
void		move_camera(double *start_pos_coordinate, double coordinate_value);
void		rotate_camera(t_para *para, double degree, double x, double y);
void		zoom_camera(double *fov, double degree, bool *run);
int			operate_with_key(int keycode, t_para *para);
int			close_window(t_scene *scene);
void		operate_with_num_keys_sp(t_para *para, int keycode);
void		operate_with_num_keys_cy(t_para *para, int keycode);
void		operate_with_num_keys_material(t_para *para, int keycode);

void		be_harebare_sky_key_p(t_para *para, int keycode);
#endif
