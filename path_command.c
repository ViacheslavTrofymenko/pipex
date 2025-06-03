/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:44:35 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/05/26 16:44:37 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_check_command(char **path_list, char *cmd)
{
	int		j;
	char	*path_fin;
	char	*path_mid;

	j = 0;
	while (path_list[j])
	{
		path_mid = ft_strjoin(path_list[j], "/");
		path_fin = ft_strjoin(path_mid, cmd);
		free(path_mid);
		if (access(path_fin, X_OK) == 0)
		{
			ft_free_str_array(path_list);
			return (path_fin);
		}
		free(path_fin);
		j++;
	}
	return (NULL);
}

char	*ft_get_path_command(char **cmd, char **envp)
{
	int		i;
	char	**path_list;
	char	*path_command;

	if (!cmd || !cmd[0] || cmd[0][0] == '\0')
		return (NULL);
	if (ft_strchr(cmd[0], '/'))
		if (access(cmd[0], X_OK) == 0)
			return (ft_strdup(cmd[0]));
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
		{
			path_list = ft_split(envp[i] + 5, ':');
			path_command = ft_check_command(path_list, cmd[0]);
			ft_free_str_array(path_list);
			return (path_command);
		}
	}
	return (NULL);
}
