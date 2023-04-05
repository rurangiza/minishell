/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:01:29 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/05 13:50:44 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_signals(void)
{
	signal(SIGINT, handle_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signals_inprocess(void)
{
	signal(SIGINT, handle_inprocess_signals);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		if (getpid() == 0)
			g_exitcode = 130;
		else
		{
			rl_redisplay();
			g_exitcode = 1;
		}
	}
}

void	handle_inprocess_signals(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		g_exitcode = 130;
	}
}

void	handle_inheredoc_signals(int signo)
{
	if (signo == SIGINT)
	{
		rl_replace_line("", 0);
		exit(1);
	}
}
