/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/28 14:55:03 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int arg_count, char **arg_list, char **envp)
{
	char		*user_input;
	t_prompt	prompt;
	t_lexer		lexer;

	(void)arg_list;
	if (arg_count != 1)
	{
		printf("Usage: ./minishell\n");
		exit(EXIT_FAILURE);
	}
	g_tools.exit_code = 0;
	signal(SIGINT, handle_signals);
	init_environment(envp);
	while (TRUE)
	{
		char *level = getenv_custm("SHLVL");
		if (level)
			printf(CGRAY CBOLD"[lvl:%s] "CRESET, level + 1);
		user_input = readline(CGREEN CBOLD"minishell $> "CRESET);
		check_user_input(user_input);
		add_history(user_input);
		lexer = lexerinho(user_input, envp);
		if (lexer.tokens)
		{
			parser(&prompt, &lexer, envp);
			if (prompt.pipe_nb == -1)
				printf("minishell: syntax error near unexpected token\n");
			if (prompt.cmds)
				execute(prompt.cmds, &prompt);
			//return (300);
		}
		free(user_input);
	}
	return (g_tools.exit_code);
}
