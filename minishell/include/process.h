/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:14 by seongele          #+#    #+#             */
/*   Updated: 2022/01/23 20:54:10 by seongele         ###   ########.fr       */
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
void	display_env(t_env *start);

#endif