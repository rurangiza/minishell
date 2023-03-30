/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/30 12:46:34 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int arg_count, char **arg_list, char **envp)
{
	char		*user_input;
	t_prompt	prompt;
	t_lexer		lexer;
	
	init_shell(&prompt, arg_count, arg_list, envp);
	while (TRUE)
	{
		signal(SIGINT, handle_signals);
		user_input = ft_readline();
		check_user_input(user_input);
		add_history(user_input);
		lexer = lexerinho(user_input, prompt.envp);
		if (lexer.tokens)
		{
			init_prompt(&prompt);
			parser(&prompt, &lexer, envp);
			if (prompt.pipe_nb == -1)
				printf("minishell: syntax error near unexpected token\n");
			if (prompt.cmds)
				execute(prompt.cmds, &prompt);
		}
	}
	return (g_exitcode);
}
