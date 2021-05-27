/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 20:52:12 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 03:15:10 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;

	if (argc < 5)
	{
		ft_putstr_fd("Usage: ./pipex file command command ... command file\n",
			STDERR_FILENO);
		return (1);
	}
	pipex = init_pipex(argc, argv, envp);
	if (!pipex)
	{
		display_error("could not initialize main structure");
		return (1);
	}
	execute_every_commands(pipex, envp);
	free_pipex(pipex);
	return (0);
}
