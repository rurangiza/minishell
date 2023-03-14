/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/14 10:49:18 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


int	main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_prompt	prompt;
	t_lexer		lexer;

	(void)ac;
	(void)av;
	init_environment(envp);
	system("clear"); // DELETE THIS
	// while (1)
	// {
	// 	printf("\033[32mVariable name:\033[0m ");
	// 	char *buffer = malloc(sizeof(char) * 15);
	// 	scanf("%s", buffer);
	// 	char *varme = get_envp_variable(buffer);
	// 	if (varme == NULL)
	// 		printf("No such variable in environment\n\n");
	// 	else
	// 		printf("%s\n\n", varme);
	// 	free(buffer);
	// }
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
