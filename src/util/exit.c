/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 08:51:24 by uminomae          #+#    #+#             */
/*   Updated: 2023/06/05 11:21:30 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	exit_put_error(char *s)
{
	printf("\x1b[38;5;198m");
	printf("Error\n");
	printf("%s\n", s);
	printf("\x1b[0m");
	exit(1);
}

void	exit_put_perror(char *s)
{
	printf("\x1b[38;5;198m");
	printf("Error\n");
	perror(s);
	printf("\x1b[0m");
	exit(1);
}
