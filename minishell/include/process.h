/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:14 by seongele          #+#    #+#             */
/*   Updated: 2022/03/13 17:19:48 by seongele         ###   ########.fr       */
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

// redirect execute fuctions
int	exec_redirect(t_list *redirect);
int	clear_redirect(t_list *redirect, int mode);
int	heredoc(char *eof);
int	input_redirect_exec(char *filename, int mode);
int	output_redirect_exec(char *filename, int mode);

// command execute fuctions
int	command(char **cmd, t_env *env);


#endif
