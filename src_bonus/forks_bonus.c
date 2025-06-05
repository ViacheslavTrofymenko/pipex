/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:14:11 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/06/05 16:53:21 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void ft_free_str_array(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
int	ft_last_child(int *fd, int *pipe_fd, char **childs, char **envp)
{
	char	*path_command;
	pid_t	num_fork;

	num_fork = fork();
	if (num_fork == 0)
	{
		close(pipe_fd[1]);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		path_command = ft_get_path_command(childs, envp);
		if (path_command)
			execve(path_command, childs, envp);
		ft_free_str_array(childs);
		exit (127);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_free_str_array(childs);
	return (0);
}

int	*ft_mid_child(int *pipe_fd_1, char **childs, char **envp, int *fd)
{
	int		*pipe_fd_2;
	pid_t	num_fork;
	char	*path_command;

	pipe_fd_2 = malloc(2 * sizeof(int));
	pipe(pipe_fd_2);
	num_fork = fork();
	if (num_fork == 0)
	{
		close(pipe_fd_1[1]);
		dup2(pipe_fd_1[0], 0);
		close(pipe_fd_1[0]);
		close(fd[0]);
		close(fd[1]);
		close(pipe_fd_2[0]);
		dup2(pipe_fd_2[1], 1);
		close(pipe_fd_2[1]);
		path_command = ft_get_path_command(childs, envp);
		if (path_command)
			execve(path_command, childs, envp);
		ft_free_str_array(childs);
	}
	return (free(pipe_fd_1), pipe_fd_2);
}

void	ft_first_child(int *fd, int *pipe_fd, char **childs, char **envp)
{
	char	*path_command;
	pid_t	num_fork;

	num_fork = fork();
	if (num_fork == 0)
	{
		close(pipe_fd[0]);
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[1]);
		path_command = ft_get_path_command(childs, envp);
		if (path_command)
			execve(path_command, childs, envp);
		ft_free_str_array(childs);
	}
}

int ft_forks(int *fd, int argc, char **argv, char **envp)
{
	int		*pipe_fd;
	char	**childs;
	int		status;
	int		i;

	pipe_fd = malloc(2 * sizeof(int));
	pipe(pipe_fd);
	childs = ft_split(argv[2], ' ');
	ft_first_child(fd, pipe_fd, childs, envp);
	i = 3;
	while (i <= argc - 3)
	{
		ft_free_str_array(childs);
		childs = ft_split(argv[i], ' ');
		pipe_fd = ft_mid_child(pipe_fd, childs, envp, fd);
		i++;
	}
	ft_free_str_array(childs);
	childs = ft_split(argv[i], ' ');
	status = ft_last_child(fd, pipe_fd, childs, envp);
	while (waitpid(-1, &status, 0) != -1)
		continue;
	return (free(pipe_fd), WEXITSTATUS(status));
}
