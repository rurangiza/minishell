/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:00 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/02 17:02:05 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * The unset command in a shell program is used to remove a variable
 * or function from the shell's environment.
 * 
 * 
 * getenv: get an environment variable 
 * tgetenv
 * 
*/

void	unset(t_token *token)
{
	int index;
	// Delete line from environment variables
	index = 0;
	while (token->envp[index])
	{
		if (token->cmd[1]
			&& ft_strncmp(token->envp[index], token->cmd[1], ft_strlen(token->cmd[1])) == 0
			&& token->envp[index][ft_strlen(token->cmd[1])] == '=')
		{
			printf("--- Found variable\n");
			printf("%s\n", token->envp[index]);
			break ;
		}
		index++;
	}
	exit(EXIT_SUCCESS);
}