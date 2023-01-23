/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:32:38 by arurangi          #+#    #+#             */
/*   Updated: 2023/01/23 17:09:50 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	* EXPANDER:
	* Takes the parser tokens as argument and interprete the environment variables into their corresponding value
	* It also handles subshells, creates pipes and handles all the opening of input-/output-redirections and storing the correct ones in the executor tokens
*/

#include "../includes/minishell.h"

void	expandor(char *token, char **envp)
{
	int	index;
	char	*tok = NULL;

	(void)index;
	(void)envp;
	// Takes the parser tokens as argument and interprete the environment variables into their corresponding value
	if (token[0] == '$') // Environment variable
	{
		token++;
		if (token[0] == '(')
		{
			int i = 0;
			while (ft_isalpha(token[i]))
				i++;
			if (token[i] == ')')
			tok = ft_substr(token, 0, ft_strlen(token) - 1);
		}
		// Go through the environment variable file
		index = 0;
		while (envp[index] != NULL)
		{
			if (tok != NULL)
			{
				if (ft_strnstr(envp[index], tok, ft_strlen(tok)))
				{
					printf("%s\n", envp[index] + ft_strlen(tok) + 1);
					return ;
				}
			}
			// If you find it, return its content
			else
			{
				if (ft_strnstr(envp[index], token, ft_strlen(token)))
				{
					printf("%s\n", envp[index] + ft_strlen(token) + 1);
					return ;
				}
			}
			index++;
		}
	}
}