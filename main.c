/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:10:50 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/05/21 13:10:53 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	char	**cmd_1;
	char	**cmd_2;

	if (argc != 5)
		return (ft_error(1, argv[0]));
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		return (ft_error(2, argv[1]));
	fd[1] = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[1] == -1)
		return (close(fd[0]), ft_error(2, argv[4]));
	cmd_1 = ft_split(argv[2], ' ');
	cmd_2 = ft_split(argv[3], ' ');
	if (!cmd_1 || !cmd_2 || !cmd_1[0] || !cmd_2[0])
		return (ft_close_and_free(fd, cmd_1, cmd_2), ft_error(2, "ft_split"));
	status = ft_forks(fd, cmd_1, cmd_2, envp);
	ft_close_and_free(fd, cmd_1, cmd_2);
	return (status);
}
