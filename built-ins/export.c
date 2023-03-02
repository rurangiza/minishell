/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:13 by akorompa          #+#    #+#             */
/*   Updated: 2023/03/02 17:05:06 by akorompa         ###   ########.fr       */
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
			if (ft_strncmp(envp[i], envp[j],))
			j++;
		}
		
	}

}

void	export(t_token *tokens)
{
	char **matrix;

	if (!tokens[1])
	{
		print_export(tokens->envp);
	}
	exit (0);
}