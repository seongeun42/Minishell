/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_parent.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seongele <seongele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 16:25:27 by sujo              #+#    #+#             */
/*   Updated: 2022/04/10 14:16:03 by seongele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sig_c_parent(void)
{
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
	exit(0);
}

static void	sig_slash_parent(void)
{
	printf("Quit : 3\n");
	exit(0);
}

void	set_signal_parent(void)
{
	signal(SIGINT, (void *)sig_c_parent);
	signal(SIGQUIT, (void *)sig_slash_parent);
}
