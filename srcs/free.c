/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 03:00:49 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 03:02:35 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_safe(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}

void	free_split(char **array)
{
	int	i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	*free_commands(char ***commands, char **path, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free_split(commands[i]);
		i++;
	}
	free(commands);
	free_split(path);
	return (NULL);
}

void	*free_pipes(t_pipes *pipes)
{
	free(pipes);
	return (NULL);
}

void	free_pipex(t_pipex *pipex)
{
	free_commands(pipex->commands, NULL, pipex->commands_count);
	close_safe(&pipex->input_fd);
	close_safe(&pipex->output_fd);
	close_all_pipes(pipex);
	free_pipes(pipex->pipes);
	free(pipex);
}
