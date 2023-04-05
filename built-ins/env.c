/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:56:40 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/05 13:49:46 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	env(t_token *tokens, t_prompt *prompt)
{
	int	i;

	if (tokens->cmd[1])
	{
		printf("env: %s: No such file or directory\n", tokens->cmd[1]);
		return ;
	}
	i = 0;
	while (prompt->envp[i])
	{
		printf("%s\n", prompt->envp[i]);
		i++;
	}
}
