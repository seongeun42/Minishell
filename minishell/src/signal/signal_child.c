/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:26:05 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 16:43:14 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_c_child(void)
{
	exit(130);
}

static void	sig_slash_child(void)
{
	exit(0);
}

void	set_signal_child(void)
{
	signal(SIGINT, (void *)sig_c_child);
	signal(SIGQUIT, (void *)sig_slash_child);
}
