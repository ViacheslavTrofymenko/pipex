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

int	ft_last_cmd(int *fd, int *pipe_fd, char **cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		return (ft_error(2, "fork failed"));
	if (pid == 0)
	{
		close(pipe_fd[1]);
		if (dup2(pipe_fd[0], 0) == -1)
			ft_error(2, "dup2 failed");
		close(pipe_fd[0]);
		if (dup2(fd[1], 1) == -1)
			ft_error(2, "dup2 failed");
		close(fd[0]);
		close(fd[1]);
		ft_exec_or_exit(cmd, envp);
	}
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	ft_free_str_array(cmd);
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

void	ft_mid_cmd(int *pipe_fd_1, char **cmd, char **envp, int *fd)
{
	int		pipe_fd_2[2];
	pid_t	pid;

	if (pipe(pipe_fd_2) == -1)
		ft_error(2, "pipe failed");
	pid = fork();
	if (pid == -1)
		ft_error(2, "fork failed");
	if (pid == 0)
	{
		ft_close_fds_in_child(pipe_fd_1, fd, pipe_fd_2);
		ft_exec_or_exit(cmd, envp);
	}
	close(pipe_fd_1[0]);
	close(pipe_fd_1[1]);
	ft_free_str_array(cmd);
	pipe_fd_1[0] = pipe_fd_2[0];
	pipe_fd_1[1] = pipe_fd_2[1];
}

void	ft_first_cmd(int *fd, int *pipe_fd, char **cmd, char **envp)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_error(2, "fork failed");
	if (pid == 0)
	{
		close(pipe_fd[0]);
		if (dup2(fd[0], 0) == -1)
			ft_error(2, "dup2 failed");
		close(fd[0]);
		close(fd[1]);
		if (dup2(pipe_fd[1], 1) == -1)
			ft_error(2, "dup2 failed");
		close(pipe_fd[1]);
		ft_exec_or_exit(cmd, envp);
	}
	ft_free_str_array(cmd);
}

int	ft_forks(int *fd, int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	char	**cmd;
	int		status;
	int		i;

	if (pipe(pipe_fd) == -1)
		return (ft_error(2, "pipe failed"));
	cmd = ft_split_or_exit(argv[2]);
	ft_first_cmd(fd, pipe_fd, cmd, envp);
	i = 3;
	while (i <= argc - 3)
	{
		cmd = ft_split_or_exit(argv[i]);
		ft_mid_cmd(pipe_fd, cmd, envp, fd);
		i++;
	}
	cmd = ft_split_or_exit(argv[i]);
	status = ft_last_cmd(fd, pipe_fd, cmd, envp);
	while (waitpid(-1, NULL, 0) != -1)
		continue ;
	return (status);
}
