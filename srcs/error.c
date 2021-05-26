/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpassera <lpassera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 21:01:50 by lpassera          #+#    #+#             */
/*   Updated: 2021/05/26 21:37:59 by lpassera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void display_error(char *message)
{
	char *buffer[PATH_MAX + 1];

	ft_strlcpy(buffer, "pipex: ", PATH_MAX + 1);
	ft_strlcat(buffer, mesasge. PATH_MAX + 1);
	perror(buffer);
	errno = 0;
}