/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:24:46 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 12:44:36 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_unset_exit(char **cmd, int size, t_env *env)
{
	if (size == 1)
	{
		if (!ft_strncmp("export", cmd[0], 7))
			g_errcode = ft_export(env, cmd);
		else if (!ft_strncmp("unset", cmd[0], 6))
			g_errcode = ft_unset(env, cmd);
		else if (!ft_strncmp("cd", cmd[0], 3))
			g_errcode = ft_cd(env, cmd[1]);
		else if (!ft_strncmp("exit", cmd[0], 5))
		{
			g_errcode = ft_exit(cmd);
			if (g_errcode >= 0)
			{
				printf("exit\n");
				exit(g_errcode);
			}
		}
		else
			return (-256);
		return (g_errcode);
	}
	return (-256);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_cre	cre;
	t_env	*env;
	t_list	*cmd;
	t_list	*redirect;

	dup2(STDIN_FILENO, BACKUP_STDIN);
	dup2(STDOUT_FILENO, BACKUP_STDOUT);
	env = NULL;
	set_signal();
	env_parsing(envp, &env);
	while (1)
	{
		cmd = ft_lstnew(0);
		redirect = ft_lstnew(0);
		str = readline("\033[32mprompt > \033[0m");
		if (str)
		{
			if (!ft_strlen(str))
				continue ;
			parsing(str, env, cmd, redirect);
			if (check_export_unset_exit((char **)cmd->next->content,
					ft_lstsize(cmd) - 1, env) != -256)
			{
				free_cmd_list(cmd);
				free_redirect_list(redirect);
			}
			else
			{
				cre.cmd = cmd;
				cre.redi = redirect;
				cre.env = env;
				cmd_redirect_exec(&cre);
			}
			add_history(str);
			free(str);
		}
		else
			break ;
	}
	return (0);
}
