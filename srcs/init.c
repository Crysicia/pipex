/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 03:02:24 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 03:02:30 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_pipex	*init_pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;

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

char	***init_commands(int argc, char *argv[], char *envp[])
{
	char	**path;
	char	***commands;
	int		i;

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

t_pipes	*init_pipes(void)
{
	t_pipes	*pipes;

	pipes = malloc(sizeof(t_pipes));
	if (!pipes)
		return (NULL);
	if (pipe(pipes->previous) || pipe(pipes->current))
		return (free_pipes(pipes));
	return (pipes);
}

char	**init_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp("PATH=", envp[i], 5))
			return (ft_split(&envp[i][5], ':'));
		i++;
	}
	return (NULL);
}
