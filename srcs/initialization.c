/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:07:15 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/29 11:30:30 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_environment(char **envp)
{
	int		index;

	index = 0;
	while (envp[index])
		index++;
	if (!getenv("OLDPWD"))
		index--;
	g_environment = malloc((index + 2) * sizeof(char *));
	if (!g_environment)
		return ;
	index = 0;
	int outdex = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "OLDPWD=", 7) != 0)
		{
			if (ft_strncmp(envp[index], "SHLVL=", 6) == 0)
				g_environment[outdex] = update_shell_level(envp[index] + 6);
			else
				g_environment[outdex] = ft_strdup(envp[index]);
			outdex++;
		}
		index++;
	}
	g_environment[outdex] = NULL;
}

char	*update_shell_level(char *variable)
{
	int		level;
	char	*new;

	level = ft_atoi(variable);
	if (level < 1)
		level = 1;
	else
		level++;
	new = ft_strjoin(ft_strdup("SHLVL="), ft_itoa(level));
	return (new);
}

void	init_shell(t_prompt *prompt, int arg_count, char **arg_list, char **envp)
{
	(void)arg_list;
	(void)prompt;
	if (arg_count != 1)
	{
		printf("Usage: ./minishell\n");
		exit(EXIT_FAILURE);
	}
	init_environment(envp);
}

void	init_prompt(t_prompt *prompt)
{
	prompt->cmds = NULL;
	prompt->path = NULL;
	prompt->saved_pid = NULL;
}