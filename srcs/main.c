/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/08 13:58:10 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_environment(char **envp)
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

void	init_directory_history(t_prompt *prompt)
{
	char *content = ft_strdup(getcwd(NULL, 0));
	ft_lstadd_front(&prompt->directory_history, ft_lstnew(content));
}

int	main(int ac, char **av, char **envp)
{
	char *user_input;
	t_prompt prompt;
	t_lexer lexer;

	(void)ac;
	(void)av;
	init_environment(envp);
	init_directory_history(&prompt);

	system("clear"); // DELETE THIS
	while (1)
	{
		user_input = readline(CGREEN CBOLD"minishell $> "CRESET);
		add_history(user_input);
		lexer = lexerinho(user_input, envp);
		parser(&prompt, &lexer, envp);

		for (int i = 0; i < prompt.pipe_nb; i++)
			prompt.cmds[i].envp = envp;
		
		execute(prompt.cmds, &prompt);
		free(user_input);
	}
	return (0);
}
