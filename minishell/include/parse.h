/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:55 by seongele          #+#    #+#             */
/*   Updated: 2022/01/23 19:52:58 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

// flag struct
typedef struct t_flag
{
	int	env_chg;
	int	space;
	int	bigq;
	int	smallq;
}	t_flag;

// parse function
t_list	*parsing(char *line, t_env* env_list);
void	line_split(char *line, t_env *env_list, t_list **head);
t_list	*make_node(char *line, t_env *env_list, int start, int end);
char	*env_find(char *line, t_env *env_list, int *start);
char	*env_substitude(char *value, char *env, int *i, int size);
char	*memory_fit(char *value);

#endif