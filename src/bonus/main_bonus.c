/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 13:22:25 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/04 16:40:33 by lhenriqu         ###   ########.fr       */
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
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		i;

	if (argc < 5)
		handle_error(E_INVALID_ARGS);
	else if (!ft_strncmp(argv[1], "here_doc", 8) && (argc < 6))
		handle_error(E_INVALID_HEREDOC);
	pipex = get_pipex();
	init_pipex(pipex, argc, argv, envp);
	exec_cmds(pipex);
	close_fds(pipex);
	i = 0;
	while (i < pipex->cmdc)
		waitpid(pipex->pids[i++], 0, 0);
	free_all(pipex);
	return (0);
}
