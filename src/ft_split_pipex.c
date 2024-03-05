/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 19:24:17 by alfofern          #+#    #+#             */
/*   Updated: 2023/03/23 12:53:52 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	ft_stringscounter(char const *s, char d, int counter, int i)
{
	while (s[i])
	{
		while (s[i] == d && s[i] != 0)
			i++;
		if ((s[i] == 39 || s[i] == 34) && s[i] != 0)
		{
			d = s[i];
			i++;
			while ((s[i] != d))
				i++;
			if (s[i++] == d)
			counter++;
			d = 32;
		}
		while (s[i] != d && s[i] != 0)
		{	
			if (s[i + 1] == d || s[i + 1] == 0)
				counter++;
			i++;
		}
	}	
	return (counter);
}

static size_t	ft_strlenc(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	*ft_stringcoma(char *s, char c, int *t)
{
	int		i;
	char	*res;

	i = 1;
	*t = ft_strlenc(&s[i], c);
	res = ft_substr(&s[i - 1], 0, *t + 2);
	if (!res)
		return (NULL);
	return (res);
}

static char	**ft_createstrings(char *s, char c, char **res, int i)
{
	int	t;
	int	j;

	j = 0;
	t = 0;
	while (s[i])
	{
		if (s[i] == 39 || s[i] == 34)
		{
			res[j++] = ft_stringcoma(&s[i], s[i], &t);
			i = i + t + 2;
			c = 32;
		}
		else if (s[i] != c)
		{	
			t = ft_strlenc(&s[i], c);
			res[j++] = ft_substr(&s[i], 0, t);
			i = i + t;
		}
		else
			i++;
	}
	res[j] = NULL;
	return (res);
}

char	**ft_split_pipex(char const *s, char c)
{
	char	**res;
	int		counter;
	int		i;

	counter = 0;
	i = 0;
	res = malloc(sizeof(char *) * (ft_stringscounter(s, c, counter, i) + 1));
	if (res == NULL)
		return (0);
	i = 0;
	res = ft_createstrings((char *)s, c, res, i);
	while (i < counter)
	{
		if (res[i] == NULL)
			ft_split_free(res);
		i++;
	}
	return (res);
}
