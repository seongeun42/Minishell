/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 17:44:43 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 17:46:16 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_env
{
	struct s_env	*next;
	char			*key;
	char			*value;
}	t_env;

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

typedef struct s_cre
{
	t_list	*cmd;
	t_list	*redi;
	t_env	*env;
}	t_cre;

#endif
