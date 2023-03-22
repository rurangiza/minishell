/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/22 12:07:24 by arurangi         ###   ########.fr       */
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
	system("clear");         //! Delete later
	while (1)
	{
		user_input = readline(CGREEN CBOLD"minishell $> "CRESET);
		check_user_input(user_input);
		add_history(user_input);
		lexer = lexerinho(user_input, envp);
		if (lexer.tokens)
		{
			parser(&prompt, &lexer, envp);
			if (prompt.cmds)
				execute(prompt.cmds, &prompt);
		}
		free(user_input);
	}
	return (0);
}
