/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:56:40 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/30 11:01:10 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_token *tokens, t_prompt *prompt)
{
	int i;

	if (tokens->cmd[1])
	{
		printf("env: %s: No such file or directory\n", tokens->cmd[1]);
		exit (1);
	}
	i = 0;
	while (prompt->envp[i])
	{
		printf("%s\n", prompt->envp[i]);
		i++;
	}
}