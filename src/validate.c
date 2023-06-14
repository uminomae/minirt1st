/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 17:18:36 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/10 13:39:12 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	validate_file_extension(char *filename)
{
	const char	*extension_dot = ft_strrchr(filename, '.');

	if (extension_dot == NULL || ft_strncmp(extension_dot, ".rt", 4) != 0)
		exit_put_error("Please enter a file name ending in \".rt\".");
}

static void	validate_arg_count(int argc)
{
	if (argc == 1)
		exit_put_error("Please enter the file name.");
	if (argc != 2)
		exit_put_error("Wrong number of arguments.");
}

static void	validate_constant(void)
{
	if (WIN_WIDTH < 100 || 800 < WIN_WIDTH)
		exit_put_error("Wrong window size.");
	if (WIN_HEIGHT < 100 || 800 < WIN_HEIGHT)
		exit_put_error("Wrong window size.");
	if (SCREEN_WIDTH != 2)
		exit_put_error("Wrong screen size.");
	if (SCREEN_DISTANCE != 1)
		exit_put_error("Wrong screen distance.");
	if (NUM_OF_THREADS != 36 || PARA_ARRAY != 37)
		exit_put_error("Incorrect thread value.");
	if (WIN_HEIGHT / NUM_OF_THREADS > AMOUNT_OF_ROWS)
		exit_put_error("Incorrect thread value.");
}

void	validate_arg(int argc, char **argv)
{
	validate_arg_count(argc);
	if (argv == NULL || argv[1] == NULL)
		exit_put_error("Wrong arguments.");
	validate_file_extension(argv[1]);
	validate_constant();
}
