/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 11:07:15 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/10 11:07:26 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_environment(char **envp)
{
	int		index;

	index = 0;
	while (envp[index])
		index++;
	g_environment = malloc((index + 1) * sizeof(char *));
	index = 0;
	while (envp[index])
	{
		g_environment[index] = ft_strdup(envp[index]);
		index++;
	}
	g_environment[index] = NULL;
}