/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alfofern <alfofern@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:12:52 by alfofern          #+#    #+#             */
/*   Updated: 2023/03/23 18:54:35 by alfofern         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>

# define N_ARGUMENTS "invalid number of arguments"
# define PATH_ERROR	"PATH acces error"
# define ERROR_IN "error infile: No such file or directory: "
# define ERROR_OUT "error outfile: No such file or directory: "
# define ERROR_CMD "command not found: "
# define ERROR_PIPE "error creating pipe"

int		pipex(int filefd[], int fd1[], char *argv[], char *env[]);
char	**ft_split_pipex(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_strtrim(char const *s1, char const *set);
/* ft_pipex_utils.c */
void	ft_execute(char*argv[], int i, char **env);
void	ft_closefds(int fd1[2], int filefd[2]);
int		ft_err_msg(char *str1, char *str2, char *str3, int ernb);
void	ft_split_free(char **res);
/* ft_pipex_parse.c */
char	*get_paths(char **env);
char	*getpath(char *argv, char **env);

#endif	