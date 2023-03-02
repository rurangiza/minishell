/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:56:40 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/02 15:10:35 by akorompa         ###   ########.fr       */
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
	while (tokens->envp[i])
	{
		printf("%s\n", tokens->envp[i]);
		i++;
	}
	exit (0);
}