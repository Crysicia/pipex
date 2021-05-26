/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 20:52:12 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 01:05:46 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
		close(pipex->input_fd);
	}
	if (placement == LAST_COMMAND)
	{
		dup2(pipex->output_fd, STDOUT_FILENO);
		close(pipex->output_fd);
	}
	return (0);
}

int execute_command(int i, t_pipex *pipex, char *envp[], int placement)
{
	int pid;
	char **command;

	int swap[2];

	ft_memcpy(swap, pipex->pipes->previous, 2 * sizeof(int));
	ft_memcpy(pipex->pipes->previous, pipex->pipes->current, 2 * sizeof(int));
	ft_memcpy(pipex->pipes->current, swap, 2 * sizeof(int));
	command = pipex->commands[i];
	pid = fork();
	if (pid < 0)
		display_error("fork");
	else if (pid == 0)
	{
		printf("Command placement: %d\n", placement);
		apply_pipes(pipex, placement);
		apply_redirections(pipex, placement);
		close(pipex->pipes->previous[PIPE_READ]);
		close(pipex->pipes->previous[PIPE_WRITE]);
		close(pipex->pipes->current[PIPE_READ]);
		close(pipex->pipes->current[PIPE_WRITE]);
		execve(command[0], command, envp);
		display_error(command[0]);
		exit(1);
	}
	else
	{
		display_pipex(pipex);
		printf("PARENT\n");
		if (placement == FIRST_COMMAND || placement == MIDDLE_COMMAND)
			close(pipex->pipes->current[PIPE_WRITE]);
		else if (placement == LAST_COMMAND)
			close(pipex->pipes->current[PIPE_READ]);
		if (placement == MIDDLE_COMMAND)
			close(pipex->pipes->previous[PIPE_READ]);
		wait(NULL);
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

int main(int argc, char *argv[], char *envp[])
{
	t_pipex *pipex;
	(void)envp;

	if (argc < 5)
		return (-1);
	pipex = init_pipex(argc, argv);
	display_pipex(pipex);
	execute_every_commands(pipex, envp);
	return (0);
}