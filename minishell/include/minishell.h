/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:16:20 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 17:54:40 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define ERR 1
# define OK 0
# define BACKUP_STDIN 100
# define BACKUP_STDOUT 101

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <termios.h>
# include <termcap.h>
# include <string.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include "struct.h"
# include "bulit_in.h"
# include "parse.h"
# include "process.h"

// util functions
char	*memory_fit(char *value);
void	double_free(char **str);
void	list_free(t_list **list);

// signal
void	set_signal(void);
void	set_signal_parent(void);
void	set_signal_child(void);

// global variant
int		g_err;

#endif
