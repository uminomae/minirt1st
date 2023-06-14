/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:36:23 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/09 17:21:58 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	init_parse(t_ptr_list *splited_alc_list)
{
	ft_memset(splited_alc_list, 0, sizeof(t_ptr_list));
}

static bool	case_of_newline_only(t_ptr_list	*splited_alc_list, char **splited)
{
	if (splited[0] == NULL)
	{
		free_alloc_list_node(splited_alc_list);
		return (true);
	}
	return (false);
}

static int	build_word_array_splited(\
t_rtfile *rtfile, char *line, t_ptr_list *splited_alc_list)
{
	rtfile->splited = ft_rt_split(line, splited_alc_list);
	if (rtfile->splited == NULL)
		exit_put_perror("ft_rt_split()");
	if (case_of_newline_only(splited_alc_list, rtfile->splited))
		return (NEWLINE);
	return (SUCCESS);
}

static ssize_t	build_scene_setting_from_array_by_identifier(\
t_rtfile *rtfile, t_ptr_list *alloc_list, char **splited)
{
	ssize_t				i;
	const char			identifer = splited[0][0];
	const t_func_ptr	*func_ptr = rtfile->func_ptr;

	i = 0;
	while (rtfile->identifer_array[i])
	{
		if (identifer == rtfile->identifer_array[i])
		{
			(*func_ptr[i])(rtfile, alloc_list, splited);
			return (i);
		}
		i++;
	}
	exit_put_error("Invalid value.");
	return (-1);
}

ssize_t	parse_line(t_rtfile *rtfile, char *line, t_ptr_list *alloc_list)
{
	t_ptr_list	splited_alc_list;
	ssize_t		id_array_num;

	init_parse(&splited_alc_list);
	if (build_word_array_splited(rtfile, line, &splited_alc_list) == NEWLINE)
		return (NONE);
	id_array_num = build_scene_setting_from_array_by_identifier(\
		rtfile, alloc_list, rtfile->splited);
	free_alloc_list_node(&splited_alc_list);
	return (id_array_num);
}
