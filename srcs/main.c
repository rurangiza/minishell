/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/14 12:01:21 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int num)
{
	(void)num;
	write(STDOUT_FILENO, "Won't die!\n", 11);
	rl_redisplay();
	return ;
}

int	main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_prompt	prompt;
	t_lexer		lexer;

	(void)ac;
	(void)av;
	init_environment(envp);
	signal(SIGINT, handler);
	system("clear"); // DELETE THIS
	g_tools.exit_code = 0;
	while (1)
	{
		user_input = readline(CGREEN CBOLD"minishell $> "CRESET);
		add_history(user_input);
		lexer = lexerinho(user_input, envp);
		parser(&prompt, &lexer, envp);
		execute(prompt.cmds, &prompt);
		free(user_input);
	}
	return (0);
}
