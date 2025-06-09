/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 13:10:50 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/06/05 16:53:31 by vtrofyme         ###   ########.fr       */
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
	exit (1);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		status;

	if (argc < 5)
		return (ft_error(1, argv[0]));
	if (ft_strncmp("here_doc", argv[1], 8) == 0)
	{
		status = ft_here_doc(argc, argv, envp);
		return (status);
	}
	fd[0] = open(argv[1], O_RDONLY);
	if (fd[0] == -1)
		return (ft_error(2, argv[1]));
	fd[1] = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[1] == -1)
		return (close(fd[0]), ft_error(2, argv[4]));
	status = ft_forks(fd, argc, argv, envp);
	close(fd[0]);
	close(fd[1]);
	return (status);
}
