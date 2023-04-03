/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:59:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/03 16:14:40 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	display_env(t_prompt *prompt, char *str)
{
	int	index;

	if (!prompt->envp)
		return ;
	index = 0;
	while (prompt->envp[index])
	{
		if (str && ft_strncmp(str, prompt->envp[index], ft_strlen(str)) == 0)
			printf(CCYAN"%s\n"CRESET, prompt->envp[index]);
		else
			printf("%s\n", prompt->envp[index]);
		index++;
	}
}

// structure
void	display_prompt(t_prompt *prompt)
{
	int	i;
	int	j;

	printf(CBOLD CCYAN"~~~~~~~~~~~~~~~ PROMPT ~~~~~~~~~~~~~~~\n"CRESET);
	if (prompt->pipe_nb < 2)
		printf("No pipes\n");
	else
		printf("%d pipes\n", prompt->pipe_nb);
	i = 0;
	while (i < prompt->pipe_nb)
	{
		printf("[%i] %s ", i, prompt->cmds[i].cmd[0]);
		j = 1;
		if (prompt->cmds[i].cmd[j])
		{
			while (prompt->cmds[i].cmd[j])
				printf("{%s}", prompt->cmds[i].cmd[j++]);
		}
		printf("\n");
		i++;
	}
	printf(CBOLD CCYAN"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"CRESET);
}

// starting
void	display_start(void)
{
	printf("\033[32m○\033[0m Starting execution..\n\n");
}

// execution tree
void	display_tree(int level, const char *function, t_token *token)
{
	int	i;

	i = 0;
	while (i < level * 2)
	{
		write(1, " ", 1);
		i++;
	}
	printf(CGRAY"|__ "CRESET);
	printf("%s()   ", function);
	printf(CBOLD CYELLOW"%s "CRESET, token->cmd[0]);
	printf("(");
	if (token->cmd && token->cmd[0])
	{
		i = 1;
		while (token->cmd[i])
			printf("%s ", token->cmd[i++]);
	}
	printf(") ");
	printf("%s ", token->cmd_path);
	printf(CGRAY"] %i %i [\033[0m \033[3;34m\n", token->infile, token->outfile);
}

// exding
void	display_end(void)
{
	write(1, "\n\033[31m✖\033[0m Finished\n\n"CRESET, 23);
}
