/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 12:58:00 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/06/05 16:55:46 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdint.h>
# include <sys/wait.h>

int		ft_forks(int *fd, int argc, char **argv, char **envp);
void	ft_free_str_array(char **str);
char	*ft_get_path_command(char **kid, char **envp);
int		ft_error(int num, char *str);
int		ft_here_doc(int argc, char **argv, char **env);
void	ft_close_and_free(int fd[2], char **cmd_1, char **cmd_2);
void	ft_close_fds_in_child(int *pipe_fd_1, int *fd, int *pipe_fd_2);
void	ft_exec_or_exit(char **cmd, char **envp);
char	**ft_split_or_exit(char *arg);

#endif
