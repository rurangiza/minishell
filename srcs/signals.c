/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:01:29 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/30 14:12:35 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
