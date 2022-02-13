/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:14 by seongele          #+#    #+#             */
/*   Updated: 2022/02/13 14:57:13 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

// envp struct
typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}	t_env;

// envp function
int		env_parsing(char *envp[], t_env **list);
char	**env_split(char const *s, char c);
char	**double_free_split(char **str);
void	display_env(t_env *start);
void	display_export(t_env *start);
char	*search_env(t_env *start, char *key_);
void	delete_env_node(t_env **start, char *key_);
int		cmd_insert_env_node(t_env **env, char *str);

#endif
