/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:46:46 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/04 12:31:05 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	set_dup2(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

static char	*error_message(char *cmd)
{
	if (!cmd || access(cmd, F_OK) != 0)
		return (C_ERROR "command not found" C_BREAK);
	else if (access(cmd, X_OK) != 0)
		return (C_ERROR "permission denied" C_BREAK);
	return ("");
}

void	exec_process(t_cmd cmd)
{
	char	*new_cmd;
	char	**args;
	t_pipex	*pipex;

	pipex = get_pipex();
	args = ft_split(cmd.cmd, ' ');
	new_cmd = handle_path(args[0], pipex->env);
	if (!new_cmd || access(new_cmd, F_OK | X_OK))
	{
		ft_printf_fd(2, "%s: %s\n", error_message(new_cmd), args[0]);
		free(new_cmd);
		ft_free_matrix((void **)args, free);
		close_fds(pipex);
		free_all(pipex);
		exit(1);
	}
	set_dup2(cmd.r_fd, cmd.w_fd);
	close_fds(pipex);
	execve(new_cmd, args, pipex->envp);
}
