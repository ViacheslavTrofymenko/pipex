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
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;
	char	**cmd_1;
	char	**cmd_2;

	if (argc != 5)
		return (ft_error(1, argv[1]));
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		return (ft_error(2, argv[1]));
	fd[1] = open(argv[4], O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd[1] == -1)
	{
		close(fd[0]);
		return (ft_error(2, argv[4]));
	}
	cmd_1 = ft_split(argv[2], ' ');
	cmd_2 = ft_split(argv[3], ' ');
	status = ft_forks(fd, cmd_1, cmd_2, envp);
	close(fd[0]);
	close(fd[1]);
	ft_free_str_array(cmd_1);
	ft_free_str_array(cmd_2);
	return (status);
}
