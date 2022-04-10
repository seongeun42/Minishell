/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:24:46 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 18:19:39 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_main(int argc, char *argv[])
{
	printf("\033[32mMinishell\033[0m\n");
	(void)argc;
	(void)argv;
}

int	check_export_unset_exit(char **cmd, int size, t_env *env)
{
	if (size == 1)
	{
		if (!ft_strncmp("export", cmd[0], 7))
			g_err = ft_export(env, cmd);
		else if (!ft_strncmp("unset", cmd[0], 6))
			g_err = ft_unset(env, cmd);
		else if (!ft_strncmp("cd", cmd[0], 3))
			g_err = ft_cd(env, cmd[1]);
		else if (!ft_strncmp("exit", cmd[0], 5))
			ft_exit(cmd);
		else
			return (-1);
		return (g_err);
	}
	return (-1);
}

static t_env	*init(int argc, char **argv, char **envp)
{
	t_env	*env;

	print_main(argc, argv);
	dup2(STDIN_FILENO, BACKUP_STDIN);
	dup2(STDOUT_FILENO, BACKUP_STDOUT);
	env = NULL;
	set_signal();
	env_parsing(envp, &env);
	return (env);
}

static void	go_to_exec(char *str, t_list *cmd, t_list *redi, t_env *env)
{
	int	idx;

	idx = -1;
	if (!ft_strlen(str))
		return ;
	while (str[++idx] == ' ')
		;
	if (str[idx] == '\0')
		return ;
	if (!parsing(str, env, cmd, redi))
	{
		if (check_export_unset_exit((char **)cmd->next->content,
				ft_lstsize(cmd) - 1, env) != -1)
		{
			free_cmd_list(cmd);
			free_redirect_list(redi);
		}
		else
			cmd_redirect_exec(cmd, redi, env);
	}
	else
		g_err = 258;
	add_history(str);
	free(str);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_env	*env;
	t_list	*cmd;
	t_list	*redirect;

	env = init(argc, argv, envp);
	while (1)
	{
		cmd = ft_lstnew(0);
		redirect = ft_lstnew(0);
		str = readline("\033[32mprompt > \033[0m");
		if (str)
			go_to_exec(str, cmd, redirect, env);
		else
		{
			printf("exit\n");
			break ;
		}
	}
	return (0);
}
