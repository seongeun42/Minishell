/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:24:46 by sujo              #+#    #+#             */
/*   Updated: 2022/03/21 12:54:27 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char	*str;
	t_env	*env;
	t_list	*cmd;
	t_list	*redirect;

	dup2(STDIN_FILENO, BACKUP_STDIN);
	dup2(STDOUT_FILENO, BACKUP_STDOUT);
	env = NULL;
	// set_signal();
	env_parsing(envp, &env);
	int k = 1;
	while(1)
	{
		cmd = ft_lstnew(0);
		redirect = ft_lstnew(0);
		str = readline("path > ");
		if (str)
		{
			// printf("[%d] %s\n", (int)ft_strlen(str), str);
			parsing(str, env, cmd, redirect);
			// cmd_redirect_exec(cmd, redirect, env);
			cmd_redirect_exec2(cmd, redirect, env);
			// parent(cmd, redirect, env);
		}
		else
			break ;
		add_history(str);
		free(str);

		// // cmd check
		// printf("cmd size: %d\n", ft_lstsize(cmd));
		// t_list *cur1 = cmd->next;
		// for (int i = 0; cur1; i++)
		// {
		// 	printf("%d번째 list\n", i);
		// 	char **ccc = (char **)cur1->content;
		// 	for (int j = 0; ccc[j]; j++)
		// 		printf("%d: %s\n", j, ccc[j]);
		// 	cur1 = cur1->next;
		// }
		// // cmd free
		// t_list *cur11 = cmd->next;
		// for (int i = 0; cur11; i++)
		// {
		// 	t_list *tmp = cur11;
		// 	double_free(cur11->content);
		// 	cur11 = cur11->next;
		// 	free(tmp);
		// }
		// free(cmd);

		// // redi check
		// printf("\nredi size: %d\n", ft_lstsize(redirect));
		// t_list *cur2 = redirect->next;
		// for (int i = 0; cur2; i++)
		// {
		// 	printf("%d번째 list\n", i);
		// 	t_list *curr = cur2->content;
		// 	for (int j = 0; curr; j++)
		// 	{
		// 		printf("%d: %s, sf:%d\n", j, (char *)curr->content, curr->split);
		// 		curr = curr->next;
		// 	}
		// 	cur2 = cur2->next;
		// }
		// // redi free
		// t_list *cur22 = redirect->next;
		// for (int i = 0; cur22; i++)
		// {
		// 	t_list *tmp2 = cur22;
		// 	t_list *curr = cur22->content;
		// 	ft_lstclear(&curr, free);
		// 	cur22 = cur22->next;
		// 	free(tmp2);
		// }
		// free(redirect);
	}
	return(0);
}
