/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 19:12:39 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/04 16:39:44 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_fds(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmdc)
	{
		close(pipex->cmds[i].r_fd);
		close(pipex->cmds[i].w_fd);
		i++;
	}
}

void	free_all(t_pipex *pipex)
{
	if (pipex->cmds)
		free(pipex->cmds);
	if (pipex->pids)
		free(pipex->pids);
	if (pipex->env.home)
		free(pipex->env.home);
	if (pipex->env.path)
		ft_free_matrix((void **)pipex->env.path, free);
}
