/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:24:46 by sujo              #+#    #+#             */
/*   Updated: 2022/01/16 17:28:53 by sujo             ###   ########.fr       */
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
			printf("[%d] %s\n", (int)ft_strlen(str), str);
		else
			break ;
		add_history(str);
		free(str);
	}
	return(0);
}
