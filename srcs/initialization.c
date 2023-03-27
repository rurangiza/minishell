/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:07:15 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/24 10:15:17 by arurangi         ###   ########.fr       */
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