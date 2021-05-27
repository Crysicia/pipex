/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 20:56:58 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/27 03:25:56 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

# define PIPE_READ 0
# define PIPE_WRITE 1

# define FIRST_COMMAND 1
# define MIDDLE_COMMAND 2
# define LAST_COMMAND 3

typedef struct s_pipes
{
	int	previous[2];
	int	current[2];
}				t_pipes;

typedef struct s_pipex
{
	int		input_fd;
	int		output_fd;
	char	***commands;
	int		commands_count;
	t_pipes	*pipes;
}				t_pipex;

void	apply_pipes(t_pipex *pipex, int placement);
void	apply_redirections(t_pipex *pipex, int placement);
void	close_all_pipes(t_pipex *pipex);
void	close_safe(int *fd);
void	display_pipex(t_pipex *pipex);
void	display_error(char *message);
void	execute_every_commands(t_pipex *pipex, char *envp[]);
void	free_split(char **array);
void	free_pipex(t_pipex *pipex);
void	*free_pipes(t_pipes *pipes);
void	*free_commands(char ***commands, char **path, int size);
char	*full_path(char *buffer, char *current_path, char *executable);
char	*get_command_path(char *command, char **path);
char	***init_commands(int argc, char *argv[], char *envp[]);
char	**init_path(char *envp[]);
t_pipes	*init_pipes(void);
t_pipex	*init_pipex(int argc, char *argv[], char *envp[]);
char	**parse_command(char *command_line, char **path);
void	swap_pipes(t_pipex *pipex);

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
void	ft_putstr_fd(char *s, int fd);
void	*ft_memcpy(void *dst, const void *src, size_t n);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);

char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_free_matrix(void **matrix, size_t size);
#endif