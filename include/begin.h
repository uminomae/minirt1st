/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 14:02:07 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 22:58:43 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BEGIN_H
# define BEGIN_H

# include "common.h"
# include "scene.h"

typedef struct s_rtfile_camera
{
	t_vec3	start_pos;
	t_vec3	direction;
	double	fov;
	t_vec3	look_at;
	double	screen_distance;
	t_vec3	view_up;
}t_rtfile_camera;

typedef struct s_ambient_light
{
	double		light_ratio;
	t_fcolor	ambient_color;
}t_ambient_light;

typedef struct s_rtfile
{
	t_shape_list	shape_list;
	t_light_list	light_list;
	t_rtfile_camera	camera;
	t_ambient_light	ambient_light;
	char			identifer_array[9];
	void			(*func_ptr[9])();
	char			**splited;
	bool			id_already_found[3];
}t_rtfile;

typedef void	(*t_func_ptr)(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited);

typedef struct s_set_cy
{
	t_vec3		position;
	double		radius;
	double		height;
}t_set_cy;

void	begin_minirt(\
t_mlx *mlx, t_ptr_list *alloc_list, char *file_name, t_scene *scene);
void	add_list_light(t_light_list *list, t_light *light);
void	add_list_shape(t_shape_list *list, t_shape *shape);
int		read_rtfile(t_rtfile *rtfile, t_ptr_list *alloc_list, char *arg_rtfile);
char	**ft_rt_split(char const *s, t_ptr_list *alloc_list);
t_light	*create_light(\
t_ptr_list	*alloc_list, t_vec3 pos, double ratio, t_fcolor illum);
int		count_splited(char **splited);
double	atod(const char *str);
void	set_sphere(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited);
void	set_plane(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited);
void	set_cylinder(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited);
void	set_ambient_light(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited);
void	set_camera(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited);
void	set_light(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited);
void	set_multi_light(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited);
bool	is_nega_one_to_one(t_vec3 v);
bool	is_number(const char *str);
void	validate_floating_point_type_array_of_char(char **splited);
bool	is_zero_to_one(double num);
bool	is_proper_rgb_value(t_fcolor colors);
bool	is_normalize(t_vec3 vec);
ssize_t	parse_line(t_rtfile *rtfile, char *line, t_ptr_list *alloc_list);
void	prepare_read_rtfile(t_rtfile *rtfile);
#endif
