/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/01 12:01:25 by arurangi         ###   ########.fr       */
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
	
	system("clear"); // DELETE THIS
	while (1)
	{
		user_input = readline(CGREEN CBOLD"minishell $> "CRESET);
		add_history(user_input);
		lexer = lexerinho(user_input, envp);
		parser(&prompt, &lexer, envp);
		
		//printf("%s\n", prompt.cmds[0].cmd[0]);
		
		// printf("%i commands\n", prompt.pipe_nb);
		for (int i = 0; i < prompt.pipe_nb; i++)
		{
			prompt.cmds[i].envp = envp;
			//printf("[%i] %s\n", i, prompt.cmds[i].cmd[0]);
		}
		execute(prompt.cmds, prompt.pipe_nb);
		free(user_input);
	}
	return (0);
}