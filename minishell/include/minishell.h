/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 06:16:20 by sujo              #+#    #+#             */
/*   Updated: 2022/02/13 17:41:05 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

# include "process.h"
# include "parse.h"
# include "bulit_in.h"

# define ERR 1
# define OK 0
# define STDIN 0
# define STDOUT 1
# define BACKUP_STDIN 100
# define BACKUP_STDOUT 101

// util functions
char	*memory_fit(char *value);
void	double_free(char **str);
void	list_free(t_list **list);

#endif
