/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lhenriqu <lhenriqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 14:01:54 by lhenriqu          #+#    #+#             */
/*   Updated: 2025/01/23 13:52:10 by lhenriqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*join_path(char *absolute, char *relative)
{
	return (ft_strjoin_with_free(ft_strjoin(absolute, "/"), relative));
}

t_env	get_env_variables(char **envp)
{
	int		i;
	t_env	env;

	i = 0;
	ft_bzero(&env, sizeof(t_env));
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			env.path = ft_split(ft_strchr(envp[i], '=') + 1, ':');
		else if (ft_strncmp(envp[i], "HOME", 3) == 0)
			env.home = ft_strdup(ft_strchr(envp[i], '=') + 1);
		i++;
	}
	return (env);
}

static char	*search_in_path(char *cmd, t_env env)
{
	int		i;
	char	*new_cmd;

	i = 0;
	new_cmd = NULL;
	if (!env.path)
		return (NULL);
	while (env.path[i])
	{
		new_cmd = join_path(env.path[i], cmd);
		if (access(new_cmd, F_OK | X_OK) == 0)
			break ;
		free(new_cmd);
		new_cmd = NULL;
		i++;
	}
	return (new_cmd);
}

char	*handle_path(char *cmd, t_env env)
{
	char	*new_cmd;

	new_cmd = NULL;
	if (ft_strchr(cmd, '/') == NULL)
	{
		new_cmd = search_in_path(cmd, env);
	}
	else
	{
		if (cmd[0] == '~')
			new_cmd = ft_strjoin(env.home, cmd + 1);
		else
			new_cmd = ft_strdup(cmd);
	}
	return (new_cmd);
}
