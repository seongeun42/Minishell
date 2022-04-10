/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 15:23:40 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 16:42:35 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_c(void)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_err = 1;
}

static void	sig_slash(void)
{
	rl_redisplay();
}

void	set_signal(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, (void *)sig_c);
	signal(SIGQUIT, (void *)sig_slash);
}
