/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/16 17:08:26 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_user_input(char *input)
{
	char *str;
	
	str = "";

	if (!input)
		return ;
}

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		if (getpid() == 0)
			g_tools.exit_code = 130;
		else
			g_tools.exit_code = 1;
	}
}

int	main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_prompt	prompt;
	t_lexer		lexer;

	(void)ac;
	(void)av;
	g_tools.exit_code = 0;
	signal(SIGINT, handle_signals);
	init_environment(envp);
	system("clear"); // DELETE THIS
	while (1)
	{
		user_input = readline(CGREEN CBOLD"minishell $> "CRESET);
		check_user_input(user_input);
		add_history(user_input);
		lexer = lexerinho(user_input, envp);
		if(lexer.tokens)
		{
			parser(&prompt, &lexer, envp);
			execute(prompt.cmds, &prompt);
		}
		free(user_input);
	}
	return (0);
}
