/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:30:42 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/04 16:40:02 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	get_cmdc(char *arg, int argc)
{
	if (!ft_strncmp(arg, "here_doc", 9))
		return (argc - 4);
	return (argc - 3);
}

static int	get_first_cmd_index(char *arg)
{
	if (!ft_strncmp(arg, "here_doc", 9))
		return (3);
	return (2);
}

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

void	init_pipex(t_pipex *p, int argc, char *argv[], char *envp[])
{
	int		cmdc;
	int		first_cmd_index;

	cmdc = get_cmdc(argv[1], argc);
	first_cmd_index = get_first_cmd_index(argv[1]);
	if (!ft_strncmp(argv[1], "here_doc", 9))
		here_doc(p, argv[2]);
	else
		p->file_in_fd = open(argv[1], O_R);
	if (p->file_in_fd < 0)
		handle_error(E_INVALID_INFILE);
	if (!ft_strncmp(argv[1], "here_doc", 9))
		p->file_out_fd = open(argv[argc - 1], O_W | O_C | O_A, 0644);
	else
		p->file_out_fd = open(argv[argc - 1], O_W | O_C | O_T, 0644);
	if (p->file_out_fd < 0)
		perror(C_ERROR "invalid output file" C_BREAK);
	p->cmds = get_commands(cmdc, (argv + first_cmd_index));
	p->env = get_env_variables(envp);
	p->pids = ft_calloc(cmdc, sizeof(int));
	p->envp = envp;
	p->cmdc = cmdc;
}
