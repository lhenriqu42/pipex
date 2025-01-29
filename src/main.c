/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:22:25 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/01/29 14:34:20 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	exec_cmd1(t_pipex *pipex)
{
	pipex->pid[0] = fork();
	if (pipex->pid[0] == PID_CHILD)
		exec_process(pipex, pipex->cmd1, FIRST);
}

static void	exec_cmd2(t_pipex *pipex)
{
	pipex->pid[1] = fork();
	if (pipex->pid[1] == PID_CHILD)
		exec_process(pipex, pipex->cmd2, LAST);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;

	pipex = get_pipex();
	if (argc != 5)
	{
		print_error("Expected: ./pipex <file_in> <cmd1> <cmd2> <file_out>");
		return (1);
	}
	init_pipex(argc, argv, envp);
	pipe(pipex->pipe);
	exec_cmd1(pipex);
	exec_cmd2(pipex);
	close_fds(pipex);
	waitpid(pipex->pid[0], 0, 0);
	waitpid(pipex->pid[1], 0, 0);
	free_all(pipex);
	return (0);
}
