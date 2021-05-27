/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 22:18:30 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 02:43:23 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void close_safe(int *fd)
{
	if (*fd == -1)
		return ;
	close(*fd);
	*fd = -1;
}

void free_split(char **array)
{
	int i;

	i = 0;
	while (array && array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void *free_commands(char ***commands, char **path, int size)
{
	int i;

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

void *free_pipes(t_pipes *pipes)
{
	free(pipes);
	return (NULL);
}

void free_pipex(t_pipex *pipex)
{
	free_commands(pipex->commands, NULL, pipex->commands_count);
	close_safe(&pipex->input_fd);
	close_safe(&pipex->output_fd);
	close_all_pipes(pipex);
	free_pipes(pipex->pipes);
	free(pipex);
}

t_pipes *init_pipes(void)
{
	t_pipes *pipes;

	pipes = malloc(sizeof(t_pipes));
	if (!pipes)
		return (NULL);
	if (pipe(pipes->previous) || pipe(pipes->current))
		return (free_pipes(pipes));
	return (pipes);
}

char **init_path(char *envp[])
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (ft_split(&envp[i][5], ':'));
		i++;
	}
	return (NULL);
}

char *full_path(char *buffer, char *current_path, char *executable)
{
	ft_strlcpy(buffer, current_path, ft_strlen(current_path) + 1);
	ft_strlcat(buffer, "/", PATH_MAX);
	ft_strlcat(buffer, executable, PATH_MAX);
	return (buffer);
}

char *get_command_path(char *command, char **path)
{
	char buffer[PATH_MAX + 1];
	int i;
	int fd;

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

char **parse_command(char *command_line, char **path)
{
	char **command;
	char *command_path;

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

char ***init_commands(int argc, char *argv[], char *envp[])
{
	char **path;
	char ***commands;
	int i;

	i = 0;
	commands = malloc(sizeof(char **) * (argc - 2));
	if (!commands)
		return (NULL);
	path = init_path(envp);
	while ((i + 2) < (argc - 1))
	{
		commands[i] = parse_command(argv[i + 2], path);
		if (!commands[i])
			return (free_commands(commands, path, i));
		i++;
	}
	commands[i] = NULL;
	free_split(path);
	return (commands);
}

t_pipex *init_pipex(int argc, char *argv[], char *envp[])
{
	t_pipex *pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->input_fd = open(argv[1], O_RDONLY);
	if (pipex->input_fd == -1)
		display_error(argv[1]);
	pipex->output_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (pipex->output_fd == -1)
		display_error(argv[argc - 1]);
	pipex->commands = init_commands(argc, argv, envp);
	pipex->commands_count = argc - 3;
	pipex->pipes = init_pipes();
	return (pipex);
}

#include <stdio.h>
void display_pipex(t_pipex *pipex)
{
	printf("---------------\nInput fd: %d\nOutput fd: %d\nPrevious pipe: [%d, %d]\nCurrent pipe: [%d, %d]\nCommands count: %d\nCommands:\n",
			pipex->input_fd,
			pipex->output_fd,
			pipex->pipes->previous[0],
			pipex->pipes->previous[1],
			pipex->pipes->current[0],
			pipex->pipes->current[1],
			pipex->commands_count
		);
	for (int i = 0; pipex->commands[i]; i++)
	{
		printf("%d: ", i);
		for (int j = 0; pipex->commands[i][j]; j++)
		{
			printf(" [%s] ", pipex->commands[i][j]);
		}
		printf("\n");
	}
}