/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 22:18:30 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 03:03:01 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*full_path(char *buffer, char *current_path, char *executable)
{
	ft_strlcpy(buffer, current_path, ft_strlen(current_path) + 1);
	ft_strlcat(buffer, "/", PATH_MAX);
	ft_strlcat(buffer, executable, PATH_MAX);
	return (buffer);
}

char	*get_command_path(char *command, char **path)
{
	char	buffer[PATH_MAX + 1];
	int		i;
	int		fd;

	i = 0;
	while (path && path[i])
	{
		fd = open(full_path(buffer, path[i], command), O_RDONLY);
		if (fd != -1)
		{
			close_safe(&fd);
			return (ft_strdup(buffer));
		}
		i++;
	}
	return (NULL);
}

char	**parse_command(char *command_line, char **path)
{
	char	**command;
	char	*command_path;

	command = ft_split(command_line, ' ');
	if (!command)
		return (NULL);
	command_path = get_command_path(command[0], path);
	if (command_path)
	{
		free(command[0]);
		command[0] = command_path;
	}
	return (command);
}
