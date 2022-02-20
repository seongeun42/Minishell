/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:24:46 by sujo              #+#    #+#             */
/*   Updated: 2022/02/20 17:57:40 by seongele         ###   ########.fr       */
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
