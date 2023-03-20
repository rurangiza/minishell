/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/20 10:21:07 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pauseBoy(char *func_name, int line, int seconds)
{
	printf("%s(), ln:%i\n", func_name, line);
	usleep(seconds * 1000000);
}

void	check_user_input(char *input)
{
	char *str;
	
	str = "";

	if (!input)
		exit (0);
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

// void	init_prompt_lexer(t_prompt *prompt, t_lexer *lexer)
// {
	
// }

int	main(int ac, char **av, char **envp)
{
	char		*user_input;
	t_prompt	prompt;
	t_lexer		lexer;

	(void)ac;
	(void)av;
	g_tools.exit_code = 0;
	//init_prompt_lexer(&prompt, &lexer);
	signal(SIGINT, handle_signals);
	init_environment(envp);
	system("clear"); // DELETE THIS
	while (1)
	{
		user_input = readline(CGREEN CBOLD"minishell $> "CRESET);
		//printf("readline %s\n", user_input);
		//printf("\nuser input = %s\n", user_input);
		check_user_input(user_input);

		add_history(user_input);
		//pauseBoy((char *)__func__, __LINE__, 2);
		lexer = lexerinho(user_input, envp);
		if (lexer.tokens)
		{
			parser(&prompt, &lexer, envp);
			execute(prompt.cmds, &prompt);
		}
		// printf("%s\n", prompt.cmds[0].cmd[0]);
		// return (0);
		//printf("free %s\n", user_input);	
		free(user_input);
	}
	return (0);
}
