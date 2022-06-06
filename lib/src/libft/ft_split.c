/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyoslee <hyoslee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 11:12:43 by hyoslee           #+#    #+#             */
/*   Updated: 2021/07/25 10:57:25 by hyoslee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

static char	**ft_malloc_error(char **array)
{
	unsigned int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static unsigned int	ft_split_count_word(char const *s, char c)
{
	unsigned int	i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] == '\0')
			break ;
		while (s[i] != c && s[i] != '\0')
			i++;
		count++;
	}
	return (count);
}

static char	*ft_str_n_duplicate(char *str, int n)
{
	char	*duplicate;

	duplicate = (char *)malloc((n + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	ft_strlcpy(duplicate, str, n + 1);
	return (duplicate);
}

static char	*ft_split2(char *start, char c, int *s_move)
{
	char	*s;

	s = start;
	*s_move = 0;
	while (*s != c && *s != '\0')
	{
		s++;
		*s_move = *s_move + 1;
	}	
	return (ft_str_n_duplicate(start, s - start));
}

char	**ft_split(char const *s, char c)
{
	unsigned int	index;
	unsigned int	words;
	char			**array;
	int				s_move;

	if (!s)
		return (0);
	index = -1;
	words = ft_split_count_word(s, c);
	array = (char **)malloc((words + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	while (++index < words)
	{
		while (*s == c)
			s++;
		if (*s == '\0')
			break ;
		array[index] = ft_split2((char *)s, c, &s_move);
		s += s_move;
		if (!array[index])
			return (ft_malloc_error(array));
	}
	array[index] = 0;
	return (array);
}
