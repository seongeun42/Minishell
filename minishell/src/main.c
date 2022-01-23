/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:24:46 by sujo              #+#    #+#             */
/*   Updated: 2022/01/23 19:57:30 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	char *str;
	t_env *env;

	env = NULL;
	env_parsing(envp, &env);
	while(1)
	{
		str = readline("path > ");
		if (str)
		{
			printf("[%d] %s\n", (int)ft_strlen(str), str);
			parsing(str, env);
		}
		else
			break ;
		add_history(str);
		free(str);
	}
	return(0);
}
