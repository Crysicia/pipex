/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 20:56:58 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 01:33:30 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

# include <stdio.h>
# include <sys/wait.h>

# define PIPE_READ 0
# define PIPE_WRITE 1

# define FIRST_COMMAND 1
# define MIDDLE_COMMAND 2
# define LAST_COMMAND 3

typedef struct s_pipes
{
	int previous[2];
	int current[2];
}				t_pipes;

typedef struct s_pipex
{
	int input_fd;
	int output_fd;
	char ***commands;
	int commands_count;
	t_pipes *pipes;
}				t_pipex;

t_pipex *init_pipex(int argc, char *argv[], char *envp[]);
void display_pipex(t_pipex *pipex);
void display_error(char *message);
void execute_every_commands(t_pipex *pipex, char *envp[]);
void swap_pipes(t_pipex *pipex);
void close_all_pipes(t_pipex *pipex);
void close_relevant_pipes(t_pipex *pipex, int placement);
int apply_pipes(t_pipex *pipex, int placement);
int apply_redirections(t_pipex *pipex, int placement);

#endif