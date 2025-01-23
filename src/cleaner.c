/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:12:39 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/01/23 13:56:29 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fds(t_pipex *pipex)
{
	if (pipex->file_in_fd != -1)
		close(pipex->file_in_fd);
	if (pipex->file_out_fd != -1)
		close(pipex->file_out_fd);
	close(pipex->pipe[READ_FD]);
	close(pipex->pipe[WRITE_FD]);
}

void	free_all(t_pipex *pipex)
{
	if (pipex->env.home)
		free(pipex->env.home);
	if (pipex->env.path)
		ft_free_matrix(pipex->env.path);
}
