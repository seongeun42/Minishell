/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:55 by seongele          #+#    #+#             */
/*   Updated: 2022/03/06 19:19:53 by seongele         ###   ########.fr       */
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
	int	pipe_close;
}	t_idx;

// parse functions
int		parsing(char *line, t_env *env, t_list *cmd, t_list *redi);
int		last_chr_check(char *line);

// line split functions
int		line_split(char *line, t_env *env, t_list ***head);
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

// make cmd array list functions
int		make_cmd_list(t_list *cmd_list);
char	**make_cmd_array(t_list *list);
char	**array_resize_and_copy(char **old, char **strs, int a_size, int *idx);
int		count_size(t_list *cur);

// make redirect list functions
int		make_redirect_list(t_list *redi);
void	split_redi_list(t_list *cur, t_list *redirect);

#endif