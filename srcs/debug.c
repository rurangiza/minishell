/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 16:59:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/28 14:39:58 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// structure
void	display_prompt(t_prompt *prompt)
{
	printf(CBOLD CCYAN"~~~~~~~~~~~~~~~ PROMPT ~~~~~~~~~~~~~~~\n"CRESET);
	if (prompt->pipe_nb < 2)
		printf("No pipes\n");
	else
		printf("%d pipes\n", prompt->pipe_nb);
	int i = 0;
	while (i < prompt->pipe_nb)
	{
		printf("[%i] %s ",i, prompt->cmds[i].cmd[0]);
		int j = 1;
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
	for (int i = 0; i < level * 2; i++)
		write(1, " ", 1);
	printf(CGRAY"|__ "CRESET);
	printf("%s()   ", function);
	printf(CBOLD CYELLOW"%s "CRESET, token->cmd[0]);
	printf("(");
	if (token->cmd && token->cmd[0])
	{
		for (int i = 1; token->cmd[i]; i++)
			printf("%s ", token->cmd[i]);
	}
	printf(") ");
	printf("%s ", token->cmd_path);
	printf(CGRAY"] %i %i [\033[0m \033[3;34m\n",token->infile, token->outfile);
}

// exding
void	display_end(void)
{
	write(1, "\n\033[31m✖\033[0m Finished\n\n"CRESET, 23);
}