/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 20:56:58 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/26 22:01:40 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft.h"

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
	t_pipes *pipes;
}				t_pipex;

#endif