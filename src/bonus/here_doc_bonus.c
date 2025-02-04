/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 15:25:07 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/04 16:26:13 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_pipex *pipex, char *delimiter)
{
	char	*line;
	int		pipe_fd[2];

	line = NULL;
	pipe(pipe_fd);
	while (1)
	{
		ft_printf(C_PURPLE "heredoc" C_BREAK "> ");
		line = get_next_line(0);
		if (!ft_strncmp(line, delimiter, ft_strlen(delimiter)))
		{
			if (line[ft_strlen(delimiter)] == '\n')
			{
				free(line);
				break ;
			}
		}
		ft_printf_fd(pipe_fd[WRITE_FD], line);
		free(line);
	}
	close_and_clear(pipe_fd[WRITE_FD]);
	pipex->file_in_fd = pipe_fd[READ_FD];
}
