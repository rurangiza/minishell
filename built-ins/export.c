/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:33:13 by akorompa          #+#    #+#             */
/*   Updated: 2023/04/05 11:41:42 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	tokens_to_export(char **cmd)
{
	int	i;
	int	count;

	if (!cmd[1])
		return (0);
	i = 1;
	count = 0;
	while (cmd[i])
	{
		count++;
		i++;
	}
	return (count);
}

int	check_export(char **cmd)
{
	int	i;
	int	j;
	int	n;

	i = 1;
	n = 0;
	if (!cmd[1])
		return (0);
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '=')
			{
				n = 1;
				break ;
			}
			j++;
		}
		if (j == (int)ft_strlen(cmd[i]))
		{
			n = 0;
			break ;
		}
		i++;
	}
	if (n != 1)
		return (1);
	return (0);
}

void	export_2(char **cpy, int size, int len, t_prompt *prompt)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		cpy[i] = ft_strdup(prompt->envp[i]);
		i++;
	}
	j = 0;
	while (++j < len + 1 )
	{
		cpy[i] = ft_strdup(prompt->cmds->cmd[j]);
		i++;
	}
	cpy[i] = 0;
}

int	export(t_token *tokens, t_prompt *prompt)
{
	char	**cpy;
	int		size;
	int		len;

	if (!tokens->cmd[1])
	{
		print_export(prompt);
		return (0);
	}
	if (check_export(tokens->cmd))
		return (printf("export : 'var_name=value'\n"));
	size = ft_tablen(prompt->envp);
	len = tokens_to_export(tokens->cmd);
	cpy = malloc(sizeof(char *) * ((size + len) + 1));
	if (!cpy)
		return (0);
	export_2(cpy, size, len, prompt);
	ft_free_matrix(prompt->envp);
	prompt->envp = ft_dup_matrix(cpy);
	return (0);
}
