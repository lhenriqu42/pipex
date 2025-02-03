/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:30:42 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/03 15:58:48 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	**get_commands(int argc, char *argv[])
{
	char	**cmds;
	int		i;
	int		j;

	cmds = ft_calloc((argc - 2), sizeof(char *));
	j = 0;
	i = 2;
	while (i < argc)
		cmds[j++] = argv[i++];
	cmds[j] = NULL;
	return (cmds);
}

static int	**get_pipes(int argc)
{
	int	**pipes;
	int	i;

	i = 0;
	pipes = ft_calloc((argc - 2), sizeof(int *));
	while (i < (argc - 3))
	{
		pipes[i] = ft_calloc(2, sizeof(int));
		i++;
	}
	pipes[i] = NULL;
}

void	init_pipex(int argc, char *argv[], char *envp[])
{
	t_pipex	*pipex;

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
	pipex->env = get_env_variables(envp);
	pipex->cmds = get_commands(argc, argv);
	pipex->envp = envp;
	pipex->pipes = get_pipes(argc);
	pipex->pids = ft_calloc((argc - 3), sizeof(int));
}
