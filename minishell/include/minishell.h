/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:16:20 by sujo              #+#    #+#             */
/*   Updated: 2022/01/16 17:27:32 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
# include <stdlib.h>

# include "../libft/libft.h"

// envp struct
typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}t_env;

// envp function
int		env_parsing(char *envp[], t_env **list);
char	**env_split(char const *s, char c);
void	display_env(t_env *start);

#endif
