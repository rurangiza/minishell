/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/01/26 16:06:29 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
	}
	return (*envp + 5);
}

char *get_cmd(char *str, char **cmd_path)
{
	char *cmd;
	char *tmp;

	while (*cmd_path)
	{
		tmp = ft_strjoin(*cmd_path, "/");
		cmd = ft_strjoin(tmp, str);
		free(tmp);
		if (access(cmd, 0) == 0)
			return(cmd);
		free(cmd);
		cmd_path++;
	}
	return (NULL);
}

void execute(t_token *parsed, char **envp)
{
	execve(parsed->cmd[0], parsed->cmd, envp);
	
}

void	lexerinho(char *prompt, t_lexer *lexer)
{
	lexer->tokens = ft_split(prompt, ' ');
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;

	char *str;
	t_lexer lexer;
	t_token *parsed;
	
	parsed = NULL;
	while (1)
	{
		str = readline("$> ");
		add_history(str);
		lexerinho(str, &lexer);
		parser(&lexer, &parsed, envp);
		// process = fork();
		// if (process == 0)
		// 	execute(&parsed, envp);
		// waitpid(process, NULL, 0);
	}
	return (0);
}