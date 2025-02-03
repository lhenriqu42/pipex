/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:12:39 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/03 15:54:56 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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
	if (pipex->cmds)
		free(pipex->cmds);
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->env.home)
		free(pipex->env.home);
	if (pipex->pipes)
		ft_free_matrix(pipex->pipes, free);
	if (pipex->env.path)
		ft_free_matrix(pipex->env.path, free);
}
