/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sujo <sujo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:25:27 by sujo              #+#    #+#             */
/*   Updated: 2022/03/21 16:25:39 by sujo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_c_parent(int signo)
{
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	exit(0);
}

static void	sig_slash_parent(int signo)
{
	printf("Quit : 3\n");
	exit(0);
}

void	set_signal_parent(void)
{
	signal(SIGINT, (void *)sig_c_parent);
	signal(SIGQUIT, (void *)sig_slash_parent);
}
