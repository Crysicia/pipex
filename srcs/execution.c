/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 01:19:13 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 02:40:29 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void clean_exit(t_pipex *pipex, char *message, int code)
{
	display_error(message);
	free_pipex(pipex);
	exit(code);
}

int execute_command(int i, t_pipex *pipex, char *envp[], int placement)
{
	int pid;
	char **command;

	swap_pipes(pipex);
	command = pipex->commands[i];
	pid = fork();
	if (pid < 0)
		clean_exit(pipex, "could not fork", 2);
	else if (pid == 0)
	{
		apply_pipes(pipex, placement);
		apply_redirections(pipex, placement);
		close_all_pipes(pipex);
		execve(command[0], command, envp);
		display_error(command[0]);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		free_pipex(pipex);
		exit(1);
	}
	return (0);
}

int get_command_placement(t_pipex *pipex, int i)
{
	if (i == 0)
		return (FIRST_COMMAND);
	if (i == pipex->commands_count - 1)
		return (LAST_COMMAND);
	return (MIDDLE_COMMAND);
}

void execute_every_commands(t_pipex *pipex, char *envp[])
{
	int i;

	i = 0;
	while (pipex->commands[i])
	{
		execute_command(i, pipex, envp, get_command_placement(pipex, i));
		i++;
	}
}