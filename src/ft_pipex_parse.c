/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_parse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:52:58 by alfofern          #+#    #+#             */
/*   Updated: 2023/03/23 11:58:20 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_paths(char **env)
{
	char	*get_paths;

	get_paths = NULL;
	while (*env++)
	{
		if (ft_strnstr((const char *)*env, "PATH=", 5))
		{
			get_paths = ft_strnstr((const char *)*env, "PATH=", 5);
			return (ft_substr(get_paths, 5, ft_strlen(get_paths) - 5));
		}
	}
	return (get_paths);
}

char	*getpath(char *argv, char **env)
{	
	char	**paths;
	char	**res;
	int		i;

	res = ft_split_pipex(argv, 32);
	if (ft_strchr(res[0], '/'))
		return (res[0]);
	argv = ft_strjoin("/", res[0]);
	paths = ft_split(get_paths(env), ':');
	i = 0;
	while (paths[i])
	{
		if (access(ft_strjoin(paths[i], argv), X_OK) == 0)
			return (ft_strjoin(paths[i], argv));
		i++;
	}
	return (NULL);
}
