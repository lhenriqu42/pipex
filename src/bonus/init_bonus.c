/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:30:42 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/04 12:33:47 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	fill_cmd(int cmdc, char *cmdv[], t_cmd *cmds, int i)
{
	static int	last_pipe_read;
	int			pipe_fd[2];
	
	cmds[i].cmd = cmdv[i];
	if (i == 0)
	{
		pipe(pipe_fd);
		cmds[i].r_fd = get_pipex()->file_in_fd;
		cmds[i].w_fd = pipe_fd[WRITE_FD];
		last_pipe_read = pipe_fd[READ_FD];
	}
	else if (i == (cmdc - 1))
	{
		cmds[i].r_fd = last_pipe_read;
		cmds[i].w_fd = get_pipex()->file_out_fd;
	}
	else
	{
		pipe(pipe_fd);
		cmds[i].r_fd = last_pipe_read;
		cmds[i].w_fd = pipe_fd[WRITE_FD];
		last_pipe_read = pipe_fd[READ_FD];
	}
}

static t_cmd	*get_commands(int cmdc, char *cmdv[])
{
	t_cmd	*cmds;
	int		i;

	cmds = ft_calloc(cmdc + 1, sizeof(t_cmd));
	i = 0;
	while (i < cmdc)
	{
		fill_cmd(cmdc, cmdv, cmds, i);
		i++;
	}
	return (cmds);
}

void	init_pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;
	int		cmdc;

	cmdc = (argc - 3);
	pipex = get_pipex();
	pipex->file_in_fd = open(argv[1], O_RDONLY);
	if (pipex->file_in_fd < 0)
	{
		perror(C_ERROR "invalid input file" C_BREAK);
		exit(1);
	}
	pipex->file_out_fd = open(
			argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644
			);
	if (pipex->file_out_fd < 0)
		perror(C_ERROR "invalid output file" C_BREAK);
	pipex->cmds = get_commands(cmdc, (argv + 2));
	pipex->env = get_env_variables(envp);
	pipex->pids = ft_calloc(cmdc, sizeof(int));
	pipex->envp = envp;
	pipex->cmdc = cmdc;
}
