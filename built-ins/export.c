/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:13 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/03 10:48:53 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int envp_len(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		i++;
	}
	return (i);
}

void	print_export(char **envp)
{
	int i;
	int j;
	int len;

	i = 0;
	len = envp_len(envp);
	while (envp[i])
	{
		j = i + 1;
		while (j < len)
		{
			//if (ft_strncmp(envp[i], envp[j],)) COMMENTÉ POUR POUVOIR COMPILER (Arsene)
			j++;
		}
		
	}

}

void	export(t_token *tokens)
{
	char **matrix;

	(void)tokens;
	(void)matrix;
	// if (!tokens[1])
	// {
	// 	print_export(tokens->envp);
	// }
	exit (0);
}