/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_rtfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 23:36:23 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 21:53:22 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	validate_identifer_duplication(\
t_rtfile *rtfile, ssize_t id_array_num)
{
	if (0 <= id_array_num && id_array_num < REQUIRED_IDENTIFIERS)
	{
		if (rtfile->id_already_found[id_array_num])
			exit_put_error("Duplicate identifier.");
		rtfile->id_already_found[id_array_num] = true;
	}
}

static void	validate_missing_value(t_rtfile *rtfile)
{
	size_t	i;
	size_t	missing;

	missing = 0;
	i = 0;
	while (i < REQUIRED_IDENTIFIERS)
	{
		if (rtfile->id_already_found[i] == false)
			missing++;
		i++;
	}
	if (1 <= missing && missing < REQUIRED_IDENTIFIERS)
		exit_put_error("Missing value.");
	if (missing == REQUIRED_IDENTIFIERS)
		exit_put_error("Opening a directory. Or missing value.");
}

int	read_rtfile(t_rtfile *rtfile, t_ptr_list *alloc_list, char *arg_rtfile)
{
	char		*line;
	ssize_t		id_array_num;
	const int	fd = open(arg_rtfile, O_RDONLY);

	if (fd == -1)
		exit_put_perror("open()");
	prepare_read_rtfile(rtfile);
	while (1)
	{
		line = get_next_line(fd);
		if (line == false)
			break ;
		id_array_num = parse_line(rtfile, line, alloc_list);
		free(line);
		validate_identifer_duplication(rtfile, id_array_num);
	}
	validate_missing_value(rtfile);
	return (0);
}
