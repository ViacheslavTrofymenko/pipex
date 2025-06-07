/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 14:18:35 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/06/05 16:59:31 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*ft_get_eof(char **argv)
{
	char	*eof;
	size_t	len;

	len = ft_strlen(argv[2]);
	eof = (char *)malloc(len + 2);
	if (!eof)
		return (NULL);
	ft_strlcpy(eof, argv[2], len + 1);
	eof[len] = '\n';
	eof[len + 1] = '\0';
	return (eof);
}

int	ft_write_temp(int *fd, char **argv, char *buffer)
{
	int		n_bytes;
	char	*eof;
	int		result;

	eof = ft_get_eof(argv);
	if (!eof)
		return (1);
	result = 0;
	while (1)
	{
		write(1, "> ", 2);
		n_bytes = read(STDIN_FILENO, buffer, 1023);
		if (n_bytes <= 0)
		{
			if (n_bytes < 0)
				result = 1;
			break;
		}
		buffer[n_bytes] = '\0';
		if (!ft_strncmp(eof, buffer, n_bytes + 1))
			break;
		write(fd[0], buffer, n_bytes);
	}
	free(eof);
	return (result);
}

int	ft_clean_and_return(int *fd, char *file, int ret)
{
	if (fd[0] >= 0)
		close(fd[0]);
	if (fd[1] >= 0)
		close(fd[1]);
	if (file)
		unlink(file);
	return (ret);
}

int	ft_here_doc(int argc, char **argv, char **env)
{
	int		fd[2];
	char	buffer[1024];
	int		status;

	if (argc != 6)
		return (ft_error(1, argv[0]));
	fd[0] = open("temp.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd[0] < 0)
		return (ft_error(2, "temp.txt"));
	fd[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd[1] < 0)
		return (ft_clean_and_return(fd, NULL, ft_error(2, argv[argc - 1])));
	if (ft_write_temp(fd, argv, buffer))
		return (ft_clean_and_return(fd, "temp.txt", 1));
	close(fd[0]);
	fd[0] = open("temp.txt", O_RDONLY, 0600);
	if (fd[0] < 0)
		return (ft_clean_and_return(fd, "temp.txt", ft_error(2, "temp.txt")));
	status = ft_forks(fd, argc - 1, argv + 1, env);
	return (ft_clean_and_return(fd, "temp.txt", status));
}
