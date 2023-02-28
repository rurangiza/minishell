/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/02/28 13:27:39 by akorompa         ###   ########.fr       */
=======
/*   Updated: 2023/02/28 17:54:21 by arurangi         ###   ########.fr       */
>>>>>>> main
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *user_input;
	t_prompt prompt;
	t_lexer lexer;

	system("clear");

	while (1)
	{
		user_input = readline(CGREEN CBOLD"minishell $> "CRESET);
		add_history(user_input);
		lexer = lexerinho(user_input, envp);
		parser(&prompt, &lexer, envp);
		execute(prompt.cmds, prompt.pipe_nb);
		free(user_input);
	}
	return (0);
}