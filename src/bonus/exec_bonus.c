/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 16:46:46 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/03 14:51:31 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	set_dup2(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
}

static void	change_input_and_output(t_pipex *pipex, int type)
{
	if (type == FIRST)
		set_dup2(pipex->file_in_fd, pipex->pipe[WRITE_FD]);
	else if (type == LAST)
		set_dup2(pipex->pipe[READ_FD], pipex->file_out_fd);
}

static char	*error_message(char *cmd)
{
	if (!cmd || access(cmd, F_OK) != 0)
		return (C_ERROR "command not found" C_BREAK);
	else if (access(cmd, X_OK) != 0)
		return (C_ERROR "permission denied" C_BREAK);
	return ("");
}

void	exec_process(t_pipex *pipex, char *cmd, int type)
{
	char	*new_cmd;
	char	**args;

	args = ft_split(cmd, ' ');
	new_cmd = handle_path(args[0], pipex->env);
	if (!new_cmd || access(new_cmd, F_OK | X_OK))
	{
		ft_printf_fd(2, "%s: %s\n", error_message(new_cmd), args[0]);
		free(new_cmd);
		ft_free_matrix(args);
		close_fds(pipex);
		free_all(pipex);
		exit(1);
	}
	change_input_and_output(pipex, type);
	close_fds(pipex);
	execve(new_cmd, args, pipex->envp);
}
