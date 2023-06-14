/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rtfile_pre.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:36:23 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/09 15:07:02 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	set_identifer_array(t_rtfile *rtfile)
{
	rtfile->identifer_array[0] = 'A';
	rtfile->identifer_array[1] = 'C';
	rtfile->identifer_array[2] = 'L';
	rtfile->identifer_array[3] = 's';
	rtfile->identifer_array[4] = 'p';
	rtfile->identifer_array[5] = 'c';
	rtfile->identifer_array[6] = '#';
	rtfile->identifer_array[7] = 'M';
	rtfile->identifer_array[8] = '\0';
}

static void	do_nothing(t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited)
{
	(void)rtfile;
	(void)alloc_list;
	(void)splited;
	return ;
}

static void	set_func_ptr_array(t_rtfile *rtfile)
{
	rtfile->func_ptr[0] = set_ambient_light;
	rtfile->func_ptr[1] = set_camera;
	rtfile->func_ptr[2] = set_light;
	rtfile->func_ptr[3] = set_sphere;
	rtfile->func_ptr[4] = set_plane;
	rtfile->func_ptr[5] = set_cylinder;
	rtfile->func_ptr[6] = do_nothing;
	rtfile->func_ptr[7] = set_multi_light;
	rtfile->func_ptr[8] = NULL;
}

void	prepare_read_rtfile(t_rtfile *rtfile)
{
	set_identifer_array(rtfile);
	set_func_ptr_array(rtfile);
}
