/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 12:47:16 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/04 16:08:26 by lhenriqu         ###   ########.fr       */
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
# define C_PURPLE "\033[35;1m"
# define C_ERROR "\033[31;1m"
# define C_BREAK "\033[0m"

// MACROS
# define PID_CHILD 0

# define O_C O_CREAT
# define O_T O_TRUNC
# define O_W O_WRONLY
# define O_R O_RDONLY
# define O_A O_APPEND


enum e_fd
{
	READ_FD = 0,
	WRITE_FD
};

typedef enum e_error
{
	E_INVALID_ARGS = 1,
	E_INVALID_INFILE,
	E_INVALID_HEREDOC,
}	t_error;

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
	int		heredoc_pipe[2];
	int		*pids;
	t_cmd	*cmds;
	int		cmdc;
	char	**envp;
	t_env	env;
}	t_pipex;

t_pipex	*get_pipex(void);
void	handle_error(t_error error);
t_env	get_env_variables(char **envp);
char	*handle_path(char*cmd, t_env env);

void	exec_process(t_cmd cmd);
void	init_pipex(t_pipex *pipex, int argc, char *argv[], char *envp[]);
void	here_doc(t_pipex *pipex, char *delimiter);
void	print_error(char *message);
void	close_fds(t_pipex *pipex);
void	free_all(t_pipex *pipex);

#endif