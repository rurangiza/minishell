/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:56:40 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/06 09:36:22 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_token *tokens)
{
	int i;

	if (tokens->cmd[1])
	{
		printf("env: %s: No such file or directory\n", tokens->cmd[1]);
		exit (1);
	}
	i = 0;
	while (g_environment[i])
	{
		printf("%s\n", g_environment[i]);
		i++;
	}
	exit (0);
}