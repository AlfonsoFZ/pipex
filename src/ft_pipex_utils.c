/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 11:52:58 by alfofern          #+#    #+#             */
/*   Updated: 2023/03/27 12:08:35 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_split_free(char **res)
{
	int	i;

	i = 0;
	while (res[i])
	{
		free(res[i]);
		i++;
	}
	free(res);
}

int	ft_err_msg(char *str1, char *str2, char *str3, int ernb)
{
	ft_putstr_fd("zsh: ", STDERR_FILENO);
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putendl_fd(str3, STDERR_FILENO);
	return (ernb);
}

void	ft_closefds(int fd1[2], int filefd[2])
{
	close(fd1[0]);
	close(fd1[1]);
	close(filefd[0]);
	close(filefd[1]);
}

void	ft_execute(char*argv[], int i, char **env)
{
	char	**res;
	char	**args;

	res = ft_split_pipex(argv[i], 32);
	args = &res[0];
	if (ft_strnstr (res[0], "awk", 3))
	{
		if (res[1][0] == '\'')
			res[1] = ft_strtrim(args[1], "\'");
		else
			res[1] = ft_strtrim(args[1], "\"");
	}
	execve(getpath(argv[i], env), args, env);
	exit(ft_err_msg("command not found", ": ", res[0], errno));
}
