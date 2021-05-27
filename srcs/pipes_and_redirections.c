/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_and_redirections.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 01:22:34 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 02:12:53 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void swap_pipes(t_pipex *pipex)
{
	int swap[2];

	ft_memcpy(swap, pipex->pipes->previous, 2 * sizeof(int));
	ft_memcpy(pipex->pipes->previous, pipex->pipes->current, 2 * sizeof(int));
	ft_memcpy(pipex->pipes->current, swap, 2 * sizeof(int));
}

void close_all_pipes(t_pipex *pipex)
{	
	close_safe(&pipex->pipes->previous[PIPE_READ]);
	close_safe(&pipex->pipes->previous[PIPE_WRITE]);
	close_safe(&pipex->pipes->current[PIPE_READ]);
	close_safe(&pipex->pipes->current[PIPE_WRITE]);
}

void close_relevant_pipes(t_pipex *pipex, int placement)
{
	if (placement == FIRST_COMMAND || placement == MIDDLE_COMMAND)
		close_safe(&pipex->pipes->current[PIPE_WRITE]);
	else if (placement == LAST_COMMAND)
		close_safe(&pipex->pipes->current[PIPE_READ]);
	if (placement == MIDDLE_COMMAND)
		close_safe(&pipex->pipes->previous[PIPE_READ]);
}

int apply_pipes(t_pipex *pipex, int placement)
{
	if (placement == FIRST_COMMAND || placement == MIDDLE_COMMAND)
		dup2(pipex->pipes->current[PIPE_WRITE], STDOUT_FILENO);
	if (placement == MIDDLE_COMMAND || placement == LAST_COMMAND)
		dup2(pipex->pipes->previous[PIPE_READ], STDIN_FILENO);
	return (0);
}

int apply_redirections(t_pipex *pipex, int placement)
{
	if (placement == FIRST_COMMAND)
	{
		dup2(pipex->input_fd, STDIN_FILENO);
		close_safe(&pipex->input_fd);
	}
	if (placement == LAST_COMMAND)
	{
		dup2(pipex->output_fd, STDOUT_FILENO);
		close_safe(&pipex->output_fd);
	}
	return (0);
}