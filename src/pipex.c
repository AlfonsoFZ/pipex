/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 17:22:29 by alfofern          #+#    #+#             */
/*   Updated: 2023/03/27 13:24:39 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	first_child(int f1, int fd1[2], char **argv, char **env)
{	
	f1 = open(argv[1], O_RDONLY);
	if (f1 < 0)
		exit(1);
	close(fd1[0]);
	dup2(f1, STDIN_FILENO);
	close(f1);
	dup2(fd1[1], STDOUT_FILENO);
	close(fd1[1]);
	ft_execute(argv, 2, env);
	exit (1);
}

int	second_child(int f2, int fd1[2], char **argv, char **env)
{
	if ((f2 < 0) || (access(argv[4], W_OK) != 0))
	{
		ft_err_msg(strerror(13), ": ", argv[4], errno);
		exit (1);
	}
	dup2(f2, STDOUT_FILENO);
	dup2(fd1[0], STDIN_FILENO);
	close(fd1[0]);
	ft_execute(argv, 3, env);
	exit(1);
}

int	weror(void)
{
	int	status;
	int	status_code;

	status_code = 127;
	wait(&status);
	if (WIFEXITED(status))
		status_code = WEXITSTATUS(status);
	status_code = 0;
	wait(&status);
	if (WIFEXITED(status))
		status_code = WEXITSTATUS(status);
	return (status_code);
}

int	pipex(int filefd[], int fd1[], char *argv[], char *env[])
{
	pid_t	pid[2];

	pipe(fd1);
	pid[0] = fork();
	if (pid[0] < 0)
		return (errno);
	if (pid[0] == 0)
		first_child(filefd[0], fd1, argv, env);
	close(fd1[1]);
	close(filefd[0]);
	filefd[1] = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	pid[1] = fork();
	if (pid[1] < 0)
		return (errno);
	if (pid[1] == 0)
		second_child(filefd[1], fd1, argv, env);
	ft_closefds(fd1, filefd);
	return (weror());
}

int	main(int argc, char *argv[], char *env[])
{
	int		filefd[2];
	int		fd1[2];

	if (argc == 5)
	{
		filefd[0] = open(argv[1], O_RDONLY);
		if (filefd[0] < 0)
			ft_err_msg(strerror(errno), ": ", argv[1], errno);
		pipex(filefd, fd1, argv, env);
	}
	else
	{
		ft_putendl_fd("Pipex: Invalid number of arguments", STDERR_FILENO);
		return (1);
	}
	return (0);
}
