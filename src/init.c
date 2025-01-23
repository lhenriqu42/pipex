/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:30:42 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/01/23 14:05:47 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	pipex->cmd1 = argv[2];
	pipex->cmd2 = argv[3];
	pipex->envp = envp;
}
