/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/02/28 13:14:47 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void execute(t_token *parsed, char **envp)
{
	execve(parsed[0].cmd_path, parsed[0].cmd, envp);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *str;
	t_prompt prompt;
	t_lexer lexer;

	while (1)
	{
		str = readline(CGREEN CBOLD"minishell $> "CRESET);
		add_history(str);
		lexer = lexerinho(str, envp);
		parser(&prompt, &lexer, envp);
		// process = fork();
		// if (process == 0)
		// 	execute(parsed, envp);
		// waitpid(process, NULL, 0);
	}
	return (0);
}