/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:14:11 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/05/26 16:14:13 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_perror(int num)
{
	if (num == 1)
		perror("pipe failed");
	else if (num == 2)
		perror("fork failed");
	else
		perror("dup2 failed");
	return (1);
}

void	ft_free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	ft_cmd_1(int *fd, int *pipe_fd, char **cmd_1, char **envp)
{
	char	*path_command;

	close(pipe_fd[0]);
	if (dup2(fd, 0) == -1)
		return (ft_perror(3));
	close(fd[0]);
	close(fd[1]);
	if (dup2(pipe_fd[1], 1) == -1)
		return (ft_perror(3));
	close(pipe_fd[1]);
	path_command = ft_get_path_command(cmd_1, envp);
	if (path_command)
		execve(path_command, cmd_1, envp);
	ft_free_str_array(cmd_1);
}

int	ft_cmd_2(int *fd, int *pipe_fd, char **cmd_2, char **envp)
{
	char	*path_command;

	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	close(pipe_fd[0]);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
	path_command = ft_get_path_command(cmd_2, envp);
	if (path_command)
		execve(path_command, cmd_2, envp);
	ft_free_str_array(cmd_2);
	exit(127);
}

int	ft_forks(int *fd, char **cmd_1, char **cmd_2, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int		status;

	if (pipe(pipe_fd) == -1)
		ft_perror(1);
	pid_1 = fork();
	if (pid_1 == -1)
		ft_perror(2);
	if (pid_1 == 0)
	{
		ft_free_str_array(cmd_2);
		ft_cmd_1(fd, pipe_fd, cmd_1, envp);
	}
	pid_2 = fork();
	if (pid_2 == -1)
		ft_perror(2);
	if (pid_2 == 0)
	{
		ft_free_str_array(cmd_1);
		status = ft_cmd_2(fd, pipe_fd, cmd_2, envp);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(pid_1, &status, 0);
	waitpid(pid_2, &status, 0);
	return (WEXITSTATUS(status));
}
