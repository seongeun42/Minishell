/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:14 by seongele          #+#    #+#             */
/*   Updated: 2022/03/20 13:13:22 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

typedef s_cmd_flag
{
	int	idx;
	int	size;
	int	isFirst;
}	t_cmd_flag;

// process fuctions
int	cmd_redirect_exec(t_list *cmd_head, t_list *redi_head, t_list *env);
int	exec_process(char **cmd, t_list *redirect, t_list *env, t_cmd_flag *flag);
int	child(char **cmd, t_list *redirect, t_list *env, int fd[]);
int	change_stdinout(t_cmd_flag *flag, int fd[]);
int	only_cmd(t_list *cmd, t_list *redi, t_list *env);


// redirect execute fuctions
int	exec_redirect(t_list *redirect);
int	clear_redirect(t_list *redirect, int mode);
int	heredoc(char *eof);
int	input_redirect_exec(char *filename, int mode);
int	output_redirect_exec(char *filename, int mode);

// command execute fuctions
int	command(char **cmd, t_env *env);


#endif
