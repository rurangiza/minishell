/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/09 21:18:21 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_environment(char **envp)
{
	int		size;
	int		original_index;
	//char	*cwd;

	size = 0;
	while (envp[size])
		size++;
	if (getenv("OLDPWD") != NULL)
		size--;
	g_environment = malloc((size + 1) * sizeof(char *));
	// cwd = ft_strdup(getcwd(NULL, 0));
	// g_environment[0] = ft_strjoin_mod(ft_strdup("OLDPWD="), cwd);
	original_index = 0;
	int global_index = 0;
	while (envp[original_index])
	{
		if (ft_strncmp(envp[original_index], "OLDPWD=", 7) != 0)
			g_environment[global_index++] = ft_strdup(envp[original_index]);
		original_index++;
	}
	g_environment[global_index] = NULL;
}

// void	init_directory_history(t_prompt *prompt)
// {
// 	ft_lstadd_front(&prompt->directory_history, ft_lstnew(content));
// }

int	main(int ac, char **av, char **envp)
{
	char *user_input;
	t_prompt prompt;
	t_lexer lexer;

	(void)ac;
	(void)av;
	init_environment(envp);
	//init_directory_history(&prompt);

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
