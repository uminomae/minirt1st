/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 23:24:08 by hioikawa          #+#    #+#             */
/*   Updated: 2023/01/28 02:09:03 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	to_i(const char *str)
{
	size_t	i;
	int		reverse_sign;
	int		ret_i;

	ret_i = 0;
	reverse_sign = -1;
	i = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		reverse_sign = (str[i] - 44);
		i = 1;
	}
	while (ft_isdigit(str[i]) == 1 && str[i] != '\0')
	{
		ret_i = ret_i * 10 - (str[i] - '0');
		i++;
	}
	return (reverse_sign * ret_i);
}

int	ft_atoi(const char *str)
{
	int			int_ret;
	size_t		i;

	int_ret = 0;
	i = 0;
	while (ft_isblank(str[i]) == 1)
		i++;
	int_ret = to_i(&str[i]);
	return (int_ret);
}
/*
int main()
{
	int    st_ret;
	int    ft_ret;
	int    ret_cmp = 0;
	char    *a;

	a = ft_itoa(INT_MIN);
	st_ret = atoi(a);
	ft_ret = ft_atoi(a); 
	ret_cmp += st_ret - ft_ret; 
	printf("(line)%3d  ""(cmp)%2d\t""(st)%d\t""(ft)%d\t""(arg1)%s\t\n" \
	, __LINE__, ret_cmp, st_ret, ft_ret, (char *)a);
}
*/
