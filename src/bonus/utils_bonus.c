/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 12:24:43 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/02/03 14:51:46 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_pipex	*get_pipex(void)
{
	static t_pipex	pipex;

	return (&pipex);
}

void	print_error(char *message)
{
	ft_printf_fd(2, C_ERROR "%s\n" C_BREAK, message);
}
