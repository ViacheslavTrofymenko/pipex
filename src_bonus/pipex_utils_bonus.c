/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 14:05:50 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/06/09 14:05:53 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	ft_error(int num, char *str)
{
	if (num == 1)
		ft_putstr_fd("Error:\n Incorrect number of arguments.\n", 2);
	if (num == 2)
		perror(str);
	if (num == 3)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not a found\n", 2);
	}
	return (1);
}

void	ft_close_and_free(int fd[2], char **cmd_1, char **cmd_2)
{
	if (cmd_1)
		ft_free_str_array(cmd_1);
	if (cmd_2)
		ft_free_str_array(cmd_2);
	close(fd[0]);
	close(fd[1]);
}

void	ft_close_fds_in_child(int *pipe_fd_1, int *fd, int *pipe_fd_2)
{
	close(pipe_fd_1[1]);
	if (dup2(pipe_fd_1[0], 0) == -1)
		ft_error(2, "dup2 failed");
	close(pipe_fd_1[0]);
	close(fd[0]);
	close(fd[1]);
	close(pipe_fd_2[0]);
	if (dup2(pipe_fd_2[1], 1) == -1)
		ft_error(2, "dup2 failed");
	close(pipe_fd_2[1]);
}

void	ft_exec_or_exit(char **cmd, char **envp)
{
	char	*path_command;

	path_command = ft_get_path_command(cmd, envp);
	if (path_command)
		execve(path_command, cmd, envp);
	ft_error(3, cmd[0]);
	ft_free_str_array(cmd);
	exit(127);
}

char	**ft_split_or_exit(char *arg)
{
	char	**cmd;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		ft_error(2, "ft_split failed");
	return (cmd);
}
