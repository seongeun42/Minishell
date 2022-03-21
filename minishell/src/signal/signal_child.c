/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:26:05 by sujo              #+#    #+#             */
/*   Updated: 2022/03/21 16:26:22 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_c_child(void)
{
	exit(0);
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
