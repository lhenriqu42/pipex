/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:47:16 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/04 12:30:38 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libs/libft/libft.h"

# include <unistd.h>
# include <stdlib.h>

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

// COLORS
# define C_SUCCESS "\033[32;3m"
# define C_ERROR "\033[31;1m"
# define C_BREAK "\033[0m"

// MACROS
# define PID_CHILD 0

enum e_fd
{
	READ_FD = 0,
	WRITE_FD
};

typedef struct t_env
{
	char	*home;
	char	**path;
}	t_env;

typedef struct s_cmd
{
	char	*cmd;
	int		r_fd;
	int		w_fd;
}	t_cmd;

typedef struct s_pipex
{
	int		file_in_fd;
	int		file_out_fd;
	int		*pids;
	t_cmd	*cmds;
	int		cmdc;
	char	**envp;
	t_env	env;
}	t_pipex;

t_pipex	*get_pipex(void);
t_env	get_env_variables(char **envp);
char	*handle_path(char*cmd, t_env env);

void	exec_process(t_cmd cmd);
void	init_pipex(int argc, char *argv[], char *envp[]);
void	print_error(char *message);
void	close_fds(t_pipex *pipex);
void	free_all(t_pipex *pipex);

#endif