/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:14 by seongele          #+#    #+#             */
/*   Updated: 2022/03/27 14:43:28 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

// process functions
int	cmd_redirect_exec(t_list *cmd, t_list *redi, t_env *env);
int	**make_pipe(int size);
int	parent(t_list *cmd, t_list *redi, t_env *env, int size);
int	child(char **cmd, t_list *redirect, t_env *env);

// redirect execute functions
int	exec_redirect(t_list *redirect);
int	heredoc(char *eof);
int	input_redirect_exec(char *filename, int mode);
int	output_redirect_exec(char *filename, int mode);

// command execute functions
int	command(char **cmd, t_env *env);




#endif
