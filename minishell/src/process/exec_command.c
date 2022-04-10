/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 14:33:34 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 12:33:22 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_built_in(char *cmd)
{
	int	size;

	size = ft_strlen(cmd) + 1;
	if (!ft_strncmp("cd", cmd, size))
		return (1);
	if (!ft_strncmp("echo", cmd, size))
		return (1);
	if (!ft_strncmp("env", cmd, size))
		return (1);
	if (!ft_strncmp("export", cmd, size))
		return (1);
	if (!ft_strncmp("pwd", cmd, size))
		return (1);
	if (!ft_strncmp("unset", cmd, size))
		return (1);
	return (0);
}

static int	execute_built_in(char **cmd, t_env *env)
{
	int	size;

	size = ft_strlen(cmd[0]) + 1;
	if (!ft_strncmp("cd", cmd[0], size))
		return (ft_cd(env, cmd[1]));
	if (!ft_strncmp("echo", cmd[0], size))
		ft_echo(cmd);
	if (!ft_strncmp("env", cmd[0], size))
		ft_env(env);
	if (!ft_strncmp("export", cmd[0], size))
		return (ft_export(env, cmd));
	if (!ft_strncmp("pwd", cmd[0], size))
		return (ft_pwd());
	if (!ft_strncmp("unset", cmd[0], size))
		ft_unset(env, cmd);
	return (OK);
}

static char	*create_new_path(char *path, char *cmd)
{
	int		size;
	char	*result;

	size = ft_strlen(path) + ft_strlen(cmd) + 1;
	result = (char *)ft_calloc(size + 1, sizeof(char));
	if (!result)
		return (0);
	ft_strlcat(result, path, size + 1);
	ft_strlcat(result, "/", size + 1);
	ft_strlcat(result, cmd, size + 1);
	return (result);
}

static int	execute_else(char **cmd, t_env *env)
{
	char	*path;
	char	**split_path;
	char	**exec_envp;
	char	*new_path;
	int		idx;

	path = search_env(env, "PATH");
	if (!path)
		return (ERR);
	split_path = ft_split(path, ':');
	exec_envp = env_get(env);
	idx = 0;
	execve(cmd[0], cmd, exec_envp);
	execve(get_pwd(), cmd, exec_envp);
	while (split_path[idx])
	{
		new_path = create_new_path(split_path[idx], cmd[0]);
		execve(new_path, cmd, exec_envp);
		free(new_path);
		idx++;
	}
	double_free(split_path);
	return (ERR);
}

int	command(char **cmd, t_env *env)
{
	int	is_built_in;

	if (cmd == NULL)
		return (ERR);
	is_built_in = check_built_in(cmd[0]);
	if (is_built_in)
		return (execute_built_in(cmd, env));
	execute_else(cmd, env);
	printf("bash: %s: command not found\n", cmd[0]);
	return (ERR);
}
