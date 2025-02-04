/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:22:25 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/04 12:22:53 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	exec_cmds(t_pipex *pipex)
{
	int	i;
	
	i = 0;
	while (i < pipex->cmdc)
	{
		pipex->pids[i] = fork();
		if (pipex->pids[i] == PID_CHILD)
			exec_process(pipex->cmds[i]);
		
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		i;
	
	pipex = get_pipex();
	if (argc != 5)
	{
		print_error("Expected: ./pipex <file_in> <cmd1> ... <cmd2> <file_out>");
		return (1);
	}
	init_pipex(argc, argv, envp);
	exec_cmds(pipex);
	close_fds(pipex);
	i = 0;
	while (i < pipex->cmdc)
		waitpid(pipex->pids[i++], 0, 0);
	free_all(pipex);
	return (0);
}
