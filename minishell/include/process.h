/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:14 by seongele          #+#    #+#             */
/*   Updated: 2022/04/10 17:26:53 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

// process functions
int		cmd_redirect_exec(t_list *cmd, t_list *redi, t_env *env);
void	sub_process(t_cre *cre, int size);
void	parent(int pid, int fd[], int idx, int size);
void	child(t_cre *cre, int fd[], int idx, int size);

// process utils functions
int		**make_pipe_space(int size);
int		free_cmd_list(t_list *cmd);
int		free_redirect_list(t_list *redi);

// redirect execute functions
int		exec_redirect(t_list *redirect);
int		heredoc(char *eof);
int		input_redirect_exec(char *filename, int mode);
int		output_redirect_exec(char *filename, int mode);

// command execute functions
int		command(char **cmd, t_env *env);

#endif
