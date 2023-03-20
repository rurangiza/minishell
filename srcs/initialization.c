/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:07:15 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/20 12:10:35 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_environment(char **envp)
{
	int		index;
	int		outdex;

	index = 0;
	while (envp[index])
		index++;
	if (!getenv("OLDPWD"))
		index--;
	g_environment = malloc((index + 1) * sizeof(char *));
	if (!g_environment)
		return ;
	index = 0;
	outdex = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], "OLDPWD=", 7) != 0)
			g_environment[outdex++] = ft_strdup(envp[index]);
		index++;
	}
	//g_environment[outdex] = NULL;
}
