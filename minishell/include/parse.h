/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:55 by seongele          #+#    #+#             */
/*   Updated: 2022/02/20 18:07:14 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

// flag struct
typedef struct s_flag
{
	int	env_chg;
	int	space;
	int	bigq;
	int	smallq;
}	t_flag;

typedef struct s_idx
{
	int	start;
	int	current;
	int	filename;
}	t_idx;

// parse functions
t_list	*parsing(char *line, t_env* env_list);

// line split functions
int		line_split(char *line, t_env *env, t_list ***head)
int		line_split_add_node(char *line, t_env *env, t_list ***h, t_idx *i);
void	line_split_last_arg(char *line, t_env *env, t_list ***h, t_idx *i);
t_list	*make_node_and_add_index(char *line, t_env *env, t_idx *i);

// make node functions
t_list	*new_node(char *value, int split_flag);
t_list	*make_node(char *line, t_env *env_list, int start, int end);
char	*env_find(char *line, t_env *env_list, int *start);
char	*env_substitude(char *value, char *env, int *i, int size);

// add space between redirect / pipe functions
char	*redirect_pipe_space_add(char *line, int cnt);
void	redirect_pipe_check_and_add(char *new_l, char **l, int *i, char c);
int		redirect_pipe_count(char *line);


#endif