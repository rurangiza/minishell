/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 12:01:29 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/30 09:14:49 by arurangi         ###   ########.fr       */
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
		// rl_redisplay();
		
		if (getpid() == 0)
		{
			g_tools.exit_code = 130;
		}
		else
		{
			rl_redisplay();
			g_tools.exit_code = 1;
		}
	}
}

void	handle_signal_process(int signo)
{
	if (signo == SIGINT)
	{
		printf("C^\n");
		rl_replace_line("", 0);
		g_tools.exit_code = 130;
	}
}
