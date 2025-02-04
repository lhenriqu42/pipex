/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 14:14:24 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/04 14:23:35 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_error(t_error error)
{
	if (error == E_INVALID_ARGS)
		print_error("Expected: ./pipex <file_in> <cmd1> ... <cmdx> <file_out>");
	if (error == E_INVALID_HEREDOC)
		print_error("Expected: ./pipex here_doc DELIMITER <cmd1> ... <cmdx> <file_out>");
	if (error == E_INVALID_INFILE)
		perror(C_ERROR "invalid input file" C_BREAK);
	exit(error);
}
