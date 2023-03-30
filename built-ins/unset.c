/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:00 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/30 11:34:35 by arurangi         ###   ########.fr       */
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
 * env: If no utility is specified, env prints out the names and values 
 * of the variables in the environment, with one name/value pair per line.
 * 
*/


void	unset(t_token *token, t_prompt *prompt)
{
	int index = 1;

	while (token->cmd[index] && is_in_environment(token->cmd[index], prompt))
	{
		if (!is_valid_identifier(token->cmd[index]))
		{
			printf("bash: unset: `%s': not a valid identifier\n", token->cmd[index]);
			return ;
		}
		// Save content of environment in buffer except the line I'll delete
		char **copy;

		int size = 0;
		while (prompt->envp[size])
			size++;
		copy = malloc(sizeof(char *) * (size + 1));

		int src_index = 0;
		int copy_index = 0;
		while (src_index < size && prompt->envp[src_index])
		{
			if (!is_variable_to_be_deleted(prompt->envp[src_index], token->cmd[index]))
			{
				copy[copy_index] = ft_strdup(prompt->envp[src_index]);
				copy_index++;
			}
			src_index++;
		}
		copy[copy_index] = NULL;
		ft_free_matrix(prompt->envp);

		prompt->envp = copy;
		
		index++;
	}
}
