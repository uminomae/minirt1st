/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_ft_rt_split.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uminomae <uminomae@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:02:50 by smizutor          #+#    #+#             */
/*   Updated: 2023/06/09 17:19:59 by uminomae         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include"minirt.h"

static int	ft_check(char c)
{
	if (c == '\0' || c == ' ' || c == ',' || c == '\n')
		return (1);
	return (0);
}

static void	ft_cpy(char *box, char *s)
{
	size_t	i;

	i = 0;
	if (box == false)
		return ;
	while (!ft_check(s[i]))
	{
		box[i] = s[i];
		i++;
	}
	box[i] = '\0';
}

static void	*ft_free(char **box)
{
	size_t	i;

	i = 0;
	while (box[i] != NULL)
	{
		free(box[i]);
		i++;
	}
	return (NULL);
}

static void	*ft_make_array(char **box, char *s, t_ptr_list *alloc_list)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		j = 0;
		if (ft_check(s[i]) == 0)
		{
			while (ft_check(s[i + j]) == 0)
				j++;
			box[k] = minirt_malloc(alloc_list, sizeof(char) * (j + 1));
			if (box[k] == false)
				return (ft_free(box));
			ft_cpy(box[k], &s[i]);
			i = i + j;
			k++;
		}
		if (i != ft_strlen(s))
			i++;
	}
	return (box);
}

char	**ft_rt_split(char const *s, t_ptr_list *alloc_list)
{	
	char	**box;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		if (ft_check(s[i]) == false)
		{
			if (ft_check(s[i + 1]))
				j++;
		}
		i++;
	}
	box = minirt_malloc(alloc_list, (sizeof(char *) * (j + 1)));
	if (box == NULL)
		return (NULL);
	box = ft_make_array(box, (char *)s, alloc_list);
	box[j] = NULL;
	return (box);
}

/*int main(void)
{
	char **box;
	int i;

	box = ft_split("aiiiiaiiiiaiiiiaiiiia",'a');
	i = 0;
	while (box[i] != NULL)
	{
		printf("%s\n", box[i]);
		i++;
	}
	i = 0;
	while (box[i++] != NULL)
		free(box[i]);
	
	box = ft_split("aaaaaaaaaaaaaa",'a');
	i = 0;
	while(box[i] != NULL)
	{
		printf("%s\n", box[i]);
		i++;
	}
	i = 0;
	while (box[i++] != NULL)
		free(box[i]);


	box = ft_split("",'a');
	i = 0;
	while(box[i] != NULL)
	{
		printf("%s\n", box[i]);
		i++;
	}
	i = 0;
	while (box[i++] != NULL)
		free(box[i]);
		
}

size_t	ft_strlen(const char *s)
{	
	size_t	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}*/