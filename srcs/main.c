/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 20:52:12 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 02:09:11 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int main(int argc, char *argv[], char *envp[])
{
	t_pipex *pipex;
	(void)envp;

	if (argc < 5)
		return (-1);
	pipex = init_pipex(argc, argv, envp);
	display_pipex(pipex);
	execute_every_commands(pipex, envp);
	free_pipex(pipex);
	return (0);
}