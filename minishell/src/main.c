/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:24:46 by sujo              #+#    #+#             */
/*   Updated: 2022/03/27 19:40:45 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_unset(char **cmd, int size, t_env *env)
{
	if (size == 1)
	{
		if (!ft_strncmp("export", cmd[0], 7))
		{
			ft_export(env, cmd);
			return (0);
		}
		if (!ft_strncmp("unset", cmd[0], 6))
		{
			ft_unset(env, cmd);
			return (0);
		}
		if (!ft_strncmp("exit", cmd[0], 5))
		{
			g_errcode = ft_exit(cmd);
			if (g_errcode >= 0)
			{
				printf("exit\n");
				exit(g_errcode);
			}
			return (g_errcode);
		}
	}
	return (1);
}

int main(int argc, char *argv[], char *envp[])
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
	int k = 1;
	while(1)
	{
		cmd = ft_lstnew(0);
		redirect = ft_lstnew(0);
		str = readline("\033[32mprompt > \033[0m");
		if (str)
		{
			if (!ft_strlen(str))
				continue ;
			parsing(str, env, cmd, redirect);
			if (check_export_unset((char **)cmd->next->content,
				ft_lstsize(cmd) - 1, env) == 1)
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
	return(0);
}
