/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 22:18:30 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/26 22:18:46 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void *free_commands(char ***commands)
{
	(void)commands;
	return (NULL);
}

void *free_pipes(t_pipes *pipes)
{
	(void)pipes;
	return (NULL);
}

void free_pipex(t_pipex *pipex)
{
	(void)pipex;
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

char **parse_command(char *command)
{
	return (ft_split(command, ' '));
}

char ***init_commands(int argc, char *argv[])
{
	char ***commands;
	int i;

	commands = malloc(sizeof(char **) * (argc - 2));
	if (!commands)
		return (NULL);
	i = 0;
	while ((i + 2) < (argc - 1))
	{
		commands[i] = parse_command(argv[i + 2]);
		if (!commands[i])
			return (free_commands(commands));
		i++;
	}
	commands[i] = NULL;
	return (commands);
}

t_pipex *init_pipex(int argc, char *argv[])
{
	t_pipex *pipex;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (NULL);
	pipex->input_fd = open(argv[1], O_RDONLY);
	pipex->output_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	pipex->commands = init_commands(argc, argv);
	pipex->pipes = init_pipes();
	return (pipex);
}

#include <stdio.h>
void display_pipex(t_pipex *pipex)
{
	printf("---------------\nInput fd: %d\nOutput fd: %d\nPrevious pipe: [%d, %d]\nCurrent pipe: [%d, %d]\nCommands:\n",
			pipex->input_fd,
			pipex->output_fd,
			pipex->pipes->previous[0],
			pipex->pipes->previous[1],
			pipex->pipes->current[0],
			pipex->pipes->current[1]
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