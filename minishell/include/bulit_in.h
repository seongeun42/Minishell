/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bulit_in.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:09:45 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 12:25:38 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BULIT_IN_H
# define BULIT_IN_H

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
void	display_env(t_env *start);
void	display_export(t_env *start);
char	*search_env(t_env *start, char *key_);
void	delete_env_node(t_env **start, char *key_);
int		cmd_insert_env_node(t_env **env, char *str);
t_env	*create_env_new_node(char *key_, char *value_);
void	update_env_node(t_env *start, char *key_, char *value_);
void	insert_new_env_node(t_env *start, t_env *new_node);
char	**env_get(t_env *env);

// built in
# define LL_MAX 9223372036854775807
void	ft_unset(t_env *start, char **key);
void	ft_env(t_env *start);
void	ft_echo(char **cmd);
int		ft_export(t_env *start, char **str);
int		ft_pwd(void);
int		ft_cd(t_env *start, char *path);
int		ft_exit(char **cmd);
char	*get_pwd(void);

#endif
