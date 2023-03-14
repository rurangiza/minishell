/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/10 14:37:10 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	create_global_environment(char **envp)
{
	//char	**buffer;
	int		index;

	index = 0;
	while (envp[index])
		index++;
	g_environment = malloc(sizeof(char *) * (index + 1));
	index = 0;
	while (envp[index])
	{
		g_environment[index] = ft_strdup(envp[index]);
		index++;
	}
	g_environment[index] = NULL;
}

void	check_user_input(char *input)
{
	char *str;
	
	str = "";

	if (!input)
		exit(0);
	if (!ft_strncmp(input, "", 1))
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_signals(int signo)
{
	if (signo == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **envp)
{
	char *user_input;
	t_prompt prompt;
	t_lexer lexer;

	(void)ac;
	(void)av;
	create_global_environment(envp);
	signal(SIGINT, handle_signals);
	system("clear"); // DELETE THIS
	while (1)
	{
		printf("%d\n", EOF);
		user_input = readline(CGREEN CBOLD"minishell $> "CRESET);
		check_user_input(user_input);
		add_history(user_input);
		lexer = lexerinho(user_input, envp);
		parser(&prompt, &lexer, envp);
		execute(prompt.cmds, prompt.pipe_nb);
		free(user_input);
	}
	return (0);
}
