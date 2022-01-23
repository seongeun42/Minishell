/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/23 16:10:55 by seongele          #+#    #+#             */
/*   Updated: 2022/01/23 16:20:15 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

// node struct
typedef struct s_list
{
	struct s_list	*next;
	void			*content;
}	t_list;

// string struct
typedef struct s_str
{
	struct s_str	*next;
	char			*value;
}	t_str;

// cmd struct
typedef struct s_cmd
{
	struct s_cmd	*next;
	char			**cmd;
}	t_cmd;

// flag struct
typedef struct t_flag
{
	int	env_chg;
	int	space;
	int	bigq;
	int	smallq;
}	t_flag;

// parse function

#endif